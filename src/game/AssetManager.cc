/*
 * Copyright (c) 2014-2015, Julien Bernard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#include "AssetManager.h"

#include <cassert>

#include <boost/filesystem.hpp>

#include "Log.h"

namespace fs = boost::filesystem;

namespace game {

  void AssetManager::addSearchDir(boost::filesystem::path path) {
    Log::info(Log::RESOURCES, "Added a new search directory: %s\n", path.string().c_str());
    m_searchdirs.emplace_back(std::move(path));
  }

  boost::filesystem::path AssetManager::getAbsolutePath(const boost::filesystem::path& relative_path) {
    if (relative_path.is_absolute()) {
      assert(fs::is_regular_file(relative_path));
      Log::info(Log::RESOURCES, "Found a resource file: %s\n", relative_path.string().c_str());
      return relative_path;
    }

    for (fs::path base : m_searchdirs) {
      fs::path absolute_path = base / relative_path;

      if (fs::is_regular_file(absolute_path)) {
        Log::info(Log::RESOURCES, "Found a resource file: %s\n", absolute_path.string().c_str());
        return absolute_path;
      }
    }

    Log::error(Log::RESOURCES, "Could not find the following file: %s\n", relative_path.c_str());
    return fs::path();
  }

}
