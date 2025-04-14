//===----------------------------------------------------------------------===//
//
// This source file is part of the SwiftNIO open source project
//
// Copyright (c) 2025 Apple Inc. and the SwiftNIO project authors
// Licensed under Apache License v2.0
//
// See LICENSE.txt for license information
// See CONTRIBUTORS.txt for the list of SwiftNIO project authors
//
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//

#if os(WASI)
import CNIOWASI

// TODO: SM: I should make a swifty api so I don't need to call freeaddrinfo. Unless I need to call freeaddrinfo with the underlying wasilibc api

package typealias addrinfo = CAddressInfo
package class CAddressInfo {

    package let ai_socktype: Int32
    package let ai_protocol: Int32
    package var pointee: CAddressInfo {
        fatalError("Not yet implemented")
        self
    }

    package let ai_addr: UnsafePointer<sockaddr>?
    package let ai_family: Int32

    package let ai_next: CAddressInfo?

    package init(
        ai_socktype: Int32,
        ai_protocol: Int32
    ) {
        fatalError("Not yet implemented")
        // TODO: SM: Implement everything and store real values here
        self.ai_socktype = ai_socktype
        self.ai_protocol = ai_protocol
        self.ai_addr = nil
        self.ai_family = 0

        self.ai_next = nil
    }
}

// https://learn.microsoft.com/en-us/windows/win32/api/ws2tcpip/nf-ws2tcpip-getaddrinfo
package func getaddrinfo(host: String, port: String, hint: CAddressInfo) -> CAddressInfo? {
    fatalError("Not yet implemented")
    // TODO: SM: Implement getaddrinfo
    return nil
}

package func freeaddrinfo(_: CAddressInfo) {
    // TODO: SM: Depending on implementation, this might not be able to be a no-op.
    
    // This is a noop for this shim's implementation, since it uses a struct and swifty api's.
}

#endif // os(WASI)


