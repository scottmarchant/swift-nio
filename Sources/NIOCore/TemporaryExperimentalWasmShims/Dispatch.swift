//
//  Dispatch.swift
//  swift-nio
//
//  Created by Scott Marchant on 3/28/25.
//

#if os(WASI)

import CNIOWASI

// TODO: SM: Quite a bit to implement here. The plan is to use Swift Concurrency
// as the backing for these wrapper functions. For the most part, there should be
// enough overlap to make things function, except for blocking API's such as
// `DispatchQueue.main.sync`. Though for those, we may be able to use
// semaphores from Posix to make a blocking API.

public class DispatchQueue: @unchecked Sendable { // TODO: SM: Make this an actor? And provide non-async functions on the actor?
    public static let main = DispatchQueue() // SM: Figure this out

    private static let _global = DispatchQueue() // SM: Figure this out
    public static func global() -> DispatchQueue {
        Self._global
    }

    public enum Attributes {
        case concurrent
    }

    private let target: DispatchQueue?

    // SM: NOTE: DispatchQueue.init looks like this in libdispatch:
    // init(label: String, qos: DispatchQoS = .unspecified, attributes: DispatchQueue.Attributes = [], autoreleaseFrequency: DispatchQueue.AutoreleaseFrequency = .inherit, target: DispatchQueue? = nil)

    public init(label: String? = nil, attributes: DispatchQueue.Attributes? = nil, target: DispatchQueue? = nil) {
        // TODO: SM: label, attributes, etc?
        self.target = target
    }

    public func async(execute work: @escaping @Sendable @convention(block) () -> Void) {
        if let target = target {
            // Recursively execute the async block on
            target.async(execute: work)
        } else {
            Task {
                work()
            }
        }
    }
}

// TODO: SM: Audit all #if canImport(Dispatch), I can either make Dispatch a module named "Dispatch", or else modify all of those closures.
// TODO: SM: Write test for this similar to code in https://dev.to/fmo91/dispatchgroup-in-swift-gg7
public class DispatchGroup: @unchecked Sendable {
    private struct WaitingBlock {
        let queue: DispatchQueue
        let work: @Sendable () -> Void

        init(queue: DispatchQueue, work: @escaping @Sendable @convention(block) () -> Void) {
            self.queue = queue
            self.work = work
        }
    }
    // TODO: SM: Thread safety

    private var activeCount = 0 {
        didSet {
            if activeCount <= 0 {
                blocksWaitingNotify.forEach { block in
                    // TODO: SM: Warnings about sendability violations here
                    block.queue.async(execute: block.work)
                }
                blocksWaitingNotify.removeAll()
            }
        }
    }
    public func enter() {
        activeCount += 1
    }

    public func leave() {
        activeCount -= 1
    }

    private var blocksWaitingNotify: [WaitingBlock] = []

    // NOTE: We can NOT support a wait function very easily with async-await. Would need to use a semaphore or something.

    public func notify(queue: DispatchQueue, execute work: @escaping @Sendable @convention(block) () -> Void) {
        // TODO: SM: What happens if nothing is waiting? Should I immediately schedule, or never execute?
        blocksWaitingNotify.append(WaitingBlock(queue: queue, work: work))
    }

    public init() {}

} // TODO: SM: Actor? APIs

// TODO: SM: Update the following comment
// TODO: SM: Could I implement this with a posix semaphore?

///
/// This is essentially a HACK that allows compiling Swift to wasm
/// while the real DispatchSemaphore implementation is implemented.
/// This relies on the fact that everything in wasm lives on the
/// single main thread.
public class DispatchSemaphore: @unchecked Sendable {
    public var value: Int

    public init(value: Int) {
        self.value = value
    }

    @discardableResult
    public func signal() -> Int {
        MainActor.assertIsolated()
        value += 1
        return value
    }

    public func wait() {
        MainActor.assertIsolated()
        assert(value > 0)
        value -= 1
    }
}

// TODO: SM: HACK: This is probably not thread safe, but
// for wasm, it shouldn't matter right now.
import struct FoundationEssentials.Data
public typealias DispatchData = Data

#endif // os(WASI)

//sm: leftoffhere:
//
//Trying to run this code, the wasm fails to compile (invalid). Also fails running from node.
//
//Not sure where problem is. Start by looking up tools to debug/disassemble the wasm binary. From node, the problem may
//be a mismatch of function parameters. Hopefully I can isolate the file, comment it out, and make it compile on wasm.
//
//Preferably don't want to play big game of needles and haystacks.
//
//Might need to enable WASI 0.2 both in my toolchain and in wasmtime for this to finally work.
//
//
//
//
//
//
//wasm-tools validate NIOWebSocketClient.wasm
//error: func 1076 failed to validate
//
//Caused by:
//    0: type mismatch: expected i32 but nothing on stack (at offset 0x7def7)
//
//
//
//
//
//
//node
//Welcome to Node.js v22.14.0.
//Type ".help" for more information.
//> const wasmBuffer = fs.readFileSync('/Users/scottm/git/ThirdParty/swift-nio/.build/wasm32-unknown-wasip1-threads/debug/NIOWebSocketClient.wasm');
//undefined
//> fined
//Uncaught ReferenceError: fined is not defined
//> let mod = await WebAssembly.compile(wasmBuffer)
//Uncaught:
//CompileError: WebAssembly.compile(): Compiling function #1076:"$ss9UnmanagedV7AtomicsE6retain2byySi_tF" failed: not enough arguments on the stack for call (need 4, got 2) @+515831
//> 
