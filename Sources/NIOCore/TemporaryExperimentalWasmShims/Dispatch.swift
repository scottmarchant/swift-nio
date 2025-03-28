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

    // SM: NOTE: DispatchQueue.init looks like this in libdispatch:
    // init(label: String, qos: DispatchQoS = .unspecified, attributes: DispatchQueue.Attributes = [], autoreleaseFrequency: DispatchQueue.AutoreleaseFrequency = .inherit, target: DispatchQueue? = nil)

    public init(label: String? = nil, attributes: DispatchQueue.Attributes? = nil, target: DispatchQueue? = nil) {

    }

    public func async(execute work: @escaping @Sendable @convention(block) () -> Void) {

    }
}

// TODO: SM: Audit all #if canImport(Dispatch), I can either make Dispatch a module named "Dispatch", or else modify all of those closures.
// TODO: SM: Write test for this similar to code in https://dev.to/fmo91/dispatchgroup-in-swift-gg7
public class DispatchGroup: @unchecked Sendable {
    public func enter() {}
    public func leave() {}

    // NOTE: We can NOT support a wait function very easily with async-await. Would need to use a semaphore or something.

    public func notify(queue: DispatchQueue, execute work: @escaping @convention(block) () -> Void) {}

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

#endif // os(WASI)
