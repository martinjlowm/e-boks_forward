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

#include "eboks/user.hpp"

#include <string>

#include "pugixml.hpp"

// Constructors
eBoks::User::User(std::string identity_number, std::string identity_type,
                  std::string nationality, std::string passphrase,
                  std::string activation_code)
    : activation_code_(activation_code),
      passphrase_(passphrase),
      identity_(identity_number, identity_type, nationality) {}

// Accessors and mutators
std::string eBoks::User::activation_code() const { return activation_code_; }
void eBoks::User::set_activation_code(std::string const &activation_code) {
  activation_code_ = activation_code;
}

std::string eBoks::User::name() const { return name_; }
void eBoks::User::set_name(std::string const &name) {
  name_ = name;
}

std::string eBoks::User::passphrase() const { return passphrase_; }
void eBoks::User::set_passphrase(std::string const &passphrase) {
  passphrase_ = passphrase;
}

eBoks::Session eBoks::User::session() const { return session_; }
void eBoks::User::set_session(Session const &session) {
  session_ = session;
}

eBoks::Identity eBoks::User::identity() const { return identity_; }
void eBoks::User::set_identity(Identity const &identity) {
  identity_ = identity;
}

// Actions
void eBoks::User::AddXML(pugi::xml_node parent) {
  pugi::xml_node node = parent.append_child("User");

  node.append_attribute("identity") = identity_.number().c_str();
  node.append_attribute("identityType") = identity_.type().c_str();
  node.append_attribute("nationality") = identity_.nationality().c_str();
  node.append_attribute("pincode") = passphrase().c_str();
}
