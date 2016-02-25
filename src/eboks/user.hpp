/*
 * Copyright (c) 2015-2016, Martin Jesper Low Madsen
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

#ifndef EBOKS_USER_HPP_
#define EBOKS_USER_HPP_

#include <string>

#include "eboks/identity.hpp"
#include "eboks/xml_constructor.hpp"

namespace eBoks {

class User : public XMLConstructor {
 public:
  User();
  User(std::string identity_number, std::string identity_type, std::string nationality,
       std::string passphrase, std::string activation_code);

  std::string activation_code() const;
  void set_activation_code(std::string const &activation_code);

  std::string name() const;
  void set_name(std::string const &name);

  std::string passphrase() const;
  void set_passphrase(std::string const &passphrase);

  bool IsShared();

  Identity identity() const;
  void set_identity(Identity const &identity);

  void AddXML(pugi::xml_node parent);

 private:
  int id_;
  int secondary_id_;
  std::string activation_code_;
  std::string name_;
  std::string passphrase_;
  bool shared_;

  Identity identity_;
};

}  // namespace eBoks

#endif  // EBOKS_USER_HPP_
