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

#ifndef EBOKS_MESSAGE_HPP_
#define EBOKS_MESSAGE_HPP_

#include <time.h>

#include <string>
#include <vector>

#include "eboks/folder.hpp"
#include "eboks/sender.hpp"

namespace eBoks {

class Attachment;

class Message {
 public:
  std::string id() const;
  void set_id(std::string const &id);

  std::string subject() const;
  void set_subject(std::string const &subject);

  time_t date() const;
  void set_date(time_t const &date);

  // Tell, Don't Ask - The Pragmatic Programmer
  bool IsRead();
  bool FromAuthority();

  std::vector<Attachment> attachments() const;
  void set_attachments(std::vector<Attachment> const &attachments);

  Folder folder() const;
  void set_folder(Folder const &folder);

  Sender sender() const;
  void set_sender(Sender const &sender);


 private:
  std::string id_;  // e.g. 2015A09A01A08B35B38B896404
  std::string subject_;
  time_t date_;

  bool from_authority_;
  bool read_;

  std::vector<Attachment> attachments_;
  Folder folder_;
  Sender sender_;
};

}  // namespace eBoks

#endif  // EBOKS_MESSAGE_HPP_
