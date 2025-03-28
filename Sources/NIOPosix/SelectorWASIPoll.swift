// TODO: SM: Header

import NIOConcurrencyHelpers
import NIOCore

#if os(WASI)
import CNIOWASI

// NOTE: SM: Look at SelectorEpoll.swift for ideas on how to implement this
// Will need to use the `poll` function`, which is available. It will be
// less efficient, but should work for small descriptor numbers

extension Selector: _SelectorBackendProtocol {
    func initialiseState0() throws {
        // TODO: SM: Implement this
    }

    func deinitAssertions0() {
        // TODO: SM: Implement this
    }

    func register0(
        selectableFD: CInt,
        fileDescriptor: CInt,
        interested: SelectorEventSet,
        registrationID: SelectorRegistrationID
    ) throws {
        // TODO: SM: Implement this
    }

    func reregister0(
        selectableFD: CInt,
        fileDescriptor: CInt,
        oldInterested: SelectorEventSet,
        newInterested: SelectorEventSet,
        registrationID: SelectorRegistrationID
    ) throws {
        // TODO: SM: Implement this
    }

    func deregister0(
        selectableFD: CInt,
        fileDescriptor: CInt,
        oldInterested: SelectorEventSet,
        registrationID: SelectorRegistrationID
    ) throws {
        // TODO: SM: Implement this
    }

    /// Apply the given `SelectorStrategy` and execute `body` once it's complete (which may produce `SelectorEvent`s to handle).
    ///
    /// - Parameters:
    ///   - strategy: The `SelectorStrategy` to apply
    ///   - body: The function to execute for each `SelectorEvent` that was produced.
    @inlinable
    func whenReady0(
        strategy: SelectorStrategy,
        onLoopBegin loopStart: () -> Void,
        _ body: (SelectorEvent<R>) throws -> Void
    ) throws {
        // TODO: SM: Implement this
    }

    /// Close the `Selector`.
    ///
    /// After closing the `Selector` it's no longer possible to use it.
    public func close0() throws {
        // TODO: SM: Implement this
    }

    // attention, this may (will!) be called from outside the event loop, ie. can't access mutable shared state (such as `self.open`)
    func wakeup0() throws {
        // TODO: SM: Implement this
    }
}

#endif // os(WASI)
