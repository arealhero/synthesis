#pragma once

#include "Element.h"
#include "FastView.h"
#include "View.h"

#include <algorithm>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace synthesis {

using FileView = FastView;

class Folder
{
 public:
  explicit Folder(std::string name)
    : name(std::move(name))
  {}

  void AddFile(const std::shared_ptr<Element>& file);
  void RemoveFile(const std::shared_ptr<Element>& file);

  void AddFolder(const std::shared_ptr<Folder>& folder);
  void RemoveFolder(const std::shared_ptr<Folder>& folder);

  [[nodiscard]] std::vector<FileView> GetViews() const;

  void Print(std::ostream& out) const;

  [[nodiscard]] std::vector<Element*> RecursiveFindFile(const std::string& filename);

 private:
  std::string name;

  std::vector<std::shared_ptr<Folder>> folders;
  FileView files;

  void Print(std::ostream& out, std::string prefix) const;
};

}
