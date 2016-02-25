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

#include "eboks/identity.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

// Constructors
eBoks::Identity::Identity() {}

eBoks::Identity::Identity(std::string number, std::string type,
                          std::string nationality)
    : nationality_(nationality), number_(number), type_(type) {}

// Accessors and mutators
std::string eBoks::Identity::nationality() const { return nationality_; }
void eBoks::Identity::set_nationality(std::string const &nationality) {
  if (nationality.length() != 2) {
    std::stringstream msg;
    msg << "`nationality' was ";
    msg << nationality;
    msg << ", but must be represented by two letters.";

    throw std::invalid_argument(msg.str());
  }

  nationality_ = nationality;
}

std::string eBoks::Identity::number() const { return number_; }
void eBoks::Identity::set_number(std::string const &number) {
  // Does identity number follow a specific rule? For `P' type, it is a
  // person's social security number. Type is set prior to number.
  if (type_ == "P") {
    if (number.length() != 10 ||
        (number.find_first_not_of("0123456789") != std::string::npos)) {
      std::stringstream msg;
      msg << "`number' was ";
      msg << number;
      msg << " and the provided identity `type' was `";
      msg << type_;
      msg << "', which should equal a social security number in the format: ";
      msg << "ddmmyyxxxx.";

      throw std::invalid_argument(msg.str());
    }
  }

  number_ = number;
}

std::string eBoks::Identity::type() const { return type_; }
void eBoks::Identity::set_type(std::string const &type) {
  if ((type != "P" && type != "X") || type.length() != 1) {
    std::stringstream msg;

    msg << "`type' was `";
    msg << type;
    msg << "', but must be either `P' or `X'.";

    throw std::invalid_argument(msg.str());
  }

  type_ = type;
}
