//
// Remove ToUnicode CMap from PDF
// https://github.com/trueroad/pdf-rm-tuc
//
// pdf-handler.cc: PDF handler class
//
// Copyright (C) 2019 Masamichi Hosoda.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
//

#include "config.h"

#include "pdf-handler.hh"

#include <iostream>
#include <regex>
#include <string>

#include <qpdf/QPDF.hh>
#include <qpdf/QPDFObjectHandle.hh>
#include <qpdf/QPDFWriter.hh>

void pdf_handler::set_pattern (const std::string &p)
{
  std::string pattern {R"(/([A-Z]{6}\+)?)" + p};
  if (verbose_)
    std::cout << "Pattern \"" << pattern << "\"" << std::endl;

  pattern_ = std::regex (pattern);
}

void pdf_handler::load ()
{
  if (verbose_)
    std::cout << "Loading \"" << filename_in_ << "\"" << std::endl;

  qpdf_.processFile (filename_in_.c_str ());
}

void pdf_handler::process ()
{
  auto objs {qpdf_.getAllObjects ()};
  for (auto o: objs)
    process_obj (o);
}

void pdf_handler::save ()
{
  if (verbose_)
    std::cout << "Writing \"" << filename_out_ << "\"" << std::endl;

  QPDFWriter w (qpdf_, filename_out_.c_str ());
  w.setLinearization (linearize_);
  w.setObjectStreamMode (object_streams_);
  w.setNewlineBeforeEndstream (newline_before_endstream_);
  w.setQDFMode (qdf_);
  w.write ();
}

void pdf_handler::process_obj (QPDFObjectHandle oh)
{
  if (verbose_)
    {
      std::cout << "Object: ID " << oh.getObjectID ()
                << ", Generation " << oh.getGeneration ()
                << ", Type " << oh.getTypeName ()
                << std::endl;
    }

  if (oh.isDictionary () && oh.hasKey ("/Type"))
    {
      if (verbose_)
        std::cout << "  /Type ";

      auto type {oh.getKey ("/Type")};
      if (type.isName ())
        {
          if (verbose_)
            std::cout << type.getName () << std::endl;
          if (std::string ("/Font") == type.getName ())
            process_font (oh);
        }
      else
        {
          if(verbose_)
            std::cout << "does not contain a name" << std::endl;
        }
    }
}

void pdf_handler::process_font (QPDFObjectHandle oh)
{
  if (oh.hasKey ("/BaseFont"))
    {
      if (verbose_)
        std::cout << "  /BaseFont ";

      auto font {oh.getKey ("/BaseFont")};
      if (font.isName ())
        {
          if (verbose_)
            std::cout << font.getName ();

          if (regex_match (font.getName (), pattern_))
            {
              if (verbose_)
                std::cout << " *** match ***" << std::endl;
              process_target (oh);
            }
          else
            {
              if (verbose_)
                std::cout << std::endl;
            }
        }
      else
        {
          if(verbose_)
            std::cout << "does not contain a name" << std::endl;
        }
    }
}

void pdf_handler::process_target (QPDFObjectHandle oh)
{
  if (oh.hasKey ("/ToUnicode"))
    {
      if (verbose_)
        std::cout << "  /ToUnicode" << std::endl;
      remove_tounicode (oh);
    }
  if (oh.hasKey ("/CIDSystemInfo"))
    {
      if (verbose_)
        std::cout << "  /CIDSystemInfo" << std::endl;
      change_ros (oh);
    }
}

bool pdf_handler::check_key_name (QPDFObjectHandle oh,
                                  const std::string &key,
                                  const std::string &name)
{
  if (!oh.hasKey (key))
    {
      if (verbose_)
        std::cout << "  does not have " << key << std::endl;
      return false;
    }

  auto n {oh.getKey (key)};
  if (!n.isName ())
    {
      if (verbose_)
        std::cout << "  " << key << " does not contain a name" << std::endl;
      return false;
    }
  if (name != n.getName ())
    {
      if (verbose_)
        std::cout << "  " << key << " is not " << n.getName () << std::endl;
      return false;
    }

  return true;
}

bool pdf_handler::check_key_string (QPDFObjectHandle oh,
                                    const std::string &key,
                                    const std::string &str)
{
  if (!oh.hasKey (key))
    {
      if (verbose_)
        std::cout << "    does not have " << key << std::endl;
      return false;
    }

  if (verbose_)
    std::cout << "    " << key;

  auto s {oh.getKey (key)};

  if (!s.isString ())
    {
      if (verbose_)
        std::cout << " does not contain a string" << std::endl;
      return false;
    }

  if (str != s.getStringValue ())
    {
      if (verbose_)
        std::cout << " is not (" << str << ")" << std::endl;
      return false;
    }

  if (verbose_)
    std::cout << " (" << str << ")" << std::endl;

  return true;
}

bool pdf_handler::check_key_int (QPDFObjectHandle oh,
                                 const std::string &key,
                                 long long i)
{
  if (!oh.hasKey (key))
    {
      if (verbose_)
        std::cout << "    does not have " << key << std::endl;
      return false;
    }

  if (verbose_)
    std::cout << "    " << key;

  auto s {oh.getKey (key)};

  if (!s.isInteger ())
    {
      if (verbose_)
        std::cout << " does not contain an integer" << std::endl;
      return false;
    }

  if (i != s.getIntValue ())
    {
      if (verbose_)
        std::cout << " is not " << i << std::endl;
      return false;
    }

  if (verbose_)
    std::cout << " " << i << std::endl;

  return true;
}

void pdf_handler::remove_tounicode (QPDFObjectHandle oh)
{
  if (check_key_name (oh, "/Subtype", "/Type0") &&
      check_key_name (oh, "/Encoding", "/Identity-H"))
    {
      if (verbose_)
        std::cout << "    removing" << std::endl;
      oh.removeKey ("/ToUnicode");
    }
}

void pdf_handler::change_ros (QPDFObjectHandle oh)
{
  if (!check_key_name (oh, "/Subtype", "/CIDFontType0"))
    return;

  auto cidsysinfo {oh.getKey ("/CIDSystemInfo")};
  if (!cidsysinfo.isDictionary ())
    {
      if (verbose_)
        std::cout << "    does not contain a dictionary"
                  << std::endl;
      return;
    }

  if (!registry_.empty () && !ordering_.empty () &&
      check_key_string (cidsysinfo, "/Registry", "Adobe") &&
      check_key_string (cidsysinfo, "/Ordering", "Identity") &&
      check_key_int (cidsysinfo, "/Supplement", 0))
    {
      if (verbose_)
        std::cout << "      changing ROS to "
                  << registry_ << "-"
                  << ordering_ << "-"
                  << supplement_ << std::endl;

      cidsysinfo.replaceKey ("/Registry",
                             QPDFObjectHandle::newString (registry_));
      cidsysinfo.replaceKey ("/Ordering",
                             QPDFObjectHandle::newString (ordering_));
      cidsysinfo.replaceKey ("/Supplement",
                             QPDFObjectHandle::newInteger (supplement_));
    }
}
