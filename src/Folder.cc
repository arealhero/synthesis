#include <Folder.h>

namespace synthesis {

void Folder::AddFile(const std::shared_ptr<Element>& file)
{
  files.Add(file.get());
}
void Folder::RemoveFile(const std::shared_ptr<Element>& file)
{
  files.Remove(file.get());
}

void Folder::AddFolder(const std::shared_ptr<Folder>& folder)
{
  folders.push_back(folder);
}
void Folder::RemoveFolder(const std::shared_ptr<Folder>& folder)
{
  auto it = std::find(folders.begin(), folders.end(), folder);
  if (it != folders.end()) {
    folders.erase(it);
  }
}

std::vector<FileView> Folder::GetViews() const
{
  std::vector<FileView> views;
  views.push_back(files);

  for (auto& folder : folders) {
    auto subfolderViews = folder->GetViews();
    views.insert(views.end(), subfolderViews.begin(), subfolderViews.end());
  }

  return views;
}

void Folder::Print(std::ostream& out) const
{
  Print(out, "");
}

std::vector<Element*> Folder::RecursiveFindFile(const std::string& filename)
{
  std::vector<Element*> foundFiles;

  Element* found = files.Find(filename.c_str());
  if (found != nullptr) {
    foundFiles.push_back(found);
  }

  for (auto& folder : folders) {
    auto subfolderFoundedFiles = folder->RecursiveFindFile(filename);

    foundFiles.insert(foundFiles.end(), subfolderFoundedFiles.begin(), subfolderFoundedFiles.end());
  }

  return foundFiles;
}

void Folder::Print(std::ostream& out, std::string prefix) const
{
  out << prefix << name;
  if (name.back() != '/') {
    out << '/';
  }
  out << '\n';

  prefix += "  ";

  for (auto& folder : folders) {
    folder->Print(out, prefix);
  }

  int count = files.Count();
  for (int i = 0; i < count; i++) {
    auto file = files.Get(i);
    out << prefix << file->name << '\n';
  }
}

}