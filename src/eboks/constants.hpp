/*
 * Copyright (c) 2015, Martin Jesper Low Madsen
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     *  Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *
 *     *  Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef EBOKS_CONSTANTS_HPP_
#define EBOKS_CONSTANTS_HPP_

#include <string>

namespace eBoks {

// Fake device ID
const std::string kFakeDeviceID = "0008baadcafef00d";

const std::string kEBoksAuthenticate = "X-EBOKS-AUTHENTICATE";

// URI parts
const std::string kURISplitter = "/";
const std::string kProtocolScheme = "https";
const std::string kBaseURI = "rest.e-boks.dk";
const std::string kServiceType = "mobile";
// Not sure what this identifier is used for.
const std::string kUnknownIdentifier = "1";
const std::string kXMLService = "xml.svc";
const std::string kLocaleTag = "en-gb";
const std::string kSession = "session";

// HTTP/1.1 methods
const std::string kGET = "GET";
const std::string kPOST = "POST";
const std::string kPUT = "PUT";
const std::string kHEAD = "HEAD";
const std::string kDELETE = "DELETE";
const std::string kTRACE = "TRACE";
const std::string kCONNECT = "CONNECT";

}  // namespace eBoks

#endif  // EBOKS_CONSTANTS_HPP_
