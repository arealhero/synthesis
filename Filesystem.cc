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
  auto aBlah = CreateFile("blah");

  a->AddFile(a12);
  a->AddFile(a13);
  a->AddFile(aBlah);

  auto b = CreateFolder("B");
  auto b12 = CreateFile("12");
  b12->properties["p"] = "2";
  auto b22 = CreateFile("22");
  auto b13 = CreateFile("13");
  auto b23 = CreateFile("23");
  auto bBlah = CreateFile("BlaH");

  b->AddFile(b12);
  b->AddFile(b22);
  b->AddFile(b13);
  b->AddFile(b23);
  b->AddFile(bBlah);

  auto c = CreateFolder("C");
  auto c12 = CreateFile("12");
  auto c13 = CreateFile("13");
  auto c123 = CreateFile("123");
  auto cBlah = CreateFile("BLaH");

  c->AddFile(c12);
  c->AddFile(c13);
  c->AddFile(c123);
  c->AddFile(cBlah);

  d->AddFolder(b);
  d->AddFolder(c);

  root->AddFolder(a);
  root->AddFolder(d);

  auto r12 = CreateFile("12");
  auto rBlah = CreateFile("12bl13");
  root->AddFile(r12);
  root->AddFile(rBlah);

  root->Print(std::cout);
  std::cout << "----------" << std::endl;

  auto FindTest = [&root](const std::string& filename, bool isCaseSensitive = true) {
    auto result = root->RecursiveFindFile(filename, isCaseSensitive);

    std::cout << "Found " << result.size() << " file" << (result.size() == 1 ? "" : "s") << " with "
              << std::quoted(filename) << " substring (case " << (isCaseSensitive ? "" : "in") << "sensitive):\n";

    for (auto& element : result) {
      std::cout << " * " << element->name << '\n';
    }

    std::cout << std::endl;
  };

  FindTest("12");

  std::cout << "Removing /12...\n" << std::endl;
  root->RemoveFile(r12);

  FindTest("12");

  FindTest("13");
  FindTest("123");

  FindTest("bl");
  FindTest("bl", false);

  FindTest("blah");
  FindTest("blah", false);

  return 0;
}
