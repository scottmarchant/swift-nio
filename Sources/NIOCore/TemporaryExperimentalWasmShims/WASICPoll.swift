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

// TODO: SM: Implement a wrapper to poll from CNIOWASI
// that performs a similar function as epoll. Obviously
// it will be less efficient. But it should work

@usableFromInline
package struct WASICPoll {
    @usableFromInline
    package struct poll_event {
        @usableFromInline
        package init() {
            // TODO: SM: Implement all the things!
        }
    }
    @usableFromInline
    package init() {
        // TODO: SM: Implement all the things!
    }
}

#endif // os(WASI)
