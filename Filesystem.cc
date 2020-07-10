#include <iomanip>
#include <iostream>
#include <memory>
#include <utility>

#include <Element.h>
#include <Folder.h>

using synthesis::Element;
using synthesis::Folder;

std::shared_ptr<Folder> CreateFolder(const std::string& name)
{
  return std::make_shared<Folder>(name);
}

std::shared_ptr<Element> CreateFile(const std::string& name)
{
  return std::make_shared<Element>(name.c_str());
}

int main()
{
  auto root = CreateFolder("/");

  auto d = CreateFolder("D");

  auto a = CreateFolder("A");
  auto a12 = CreateFile("12");
  a12->properties["p"] = "1";
  auto a13 = CreateFile("13");

  a->AddFile(a12);
  a->AddFile(a13);

  auto b = CreateFolder("B");
  auto b12 = CreateFile("12");
  b12->properties["p"] = "2";
  auto b22 = CreateFile("22");
  auto b13 = CreateFile("13");
  auto b23 = CreateFile("23");

  b->AddFile(b12);
  b->AddFile(b22);
  b->AddFile(b13);
  b->AddFile(b23);

  auto c = CreateFolder("C");
  auto c12 = CreateFile("12");
  auto c13 = CreateFile("13");
  auto c123 = CreateFile("123");

  c->AddFile(c12);
  c->AddFile(c13);
  c->AddFile(c123);

  d->AddFolder(b);
  d->AddFolder(c);

  root->AddFolder(a);
  root->AddFolder(d);

  auto r12 = CreateFile("12");
  root->AddFile(r12);

  root->Print(std::cout);
  std::cout << "----------" << std::endl;

  auto FindTest = [&root](const std::string& filename) {
    auto result = root->RecursiveFindFile(filename);

    std::cout << "Found " << result.size() << " file" << (result.size() == 1 ? "" : "s") << " named "
              << std::quoted(filename) << std::endl;
  };

  FindTest("12");

  std::cout << "Removing /12..." << std::endl;
  root->RemoveFile(r12);

  FindTest("12");

  FindTest("13");
  FindTest("123");

  return 0;
}
