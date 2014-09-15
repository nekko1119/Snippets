#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <new>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

struct entity
{
  std::int32_t position;
  std::uint32_t size;
};

std::unordered_map<std::string, entity> entities;

template <class T, std::size_t N = sizeof(T)>
std::enable_if_t<std::is_trivial<T>::value, T> read_trivial(std::ifstream& ifs)
{
  unsigned char buffer[N];
  ifs.read(reinterpret_cast<char*>(buffer), N);
  return *reinterpret_cast<T*>(buffer);
}

void decode_archive(std::ifstream& archive)
{
  archive.seekg(-4, std::ifstream::end);
  std::uint32_t const header_start = read_trivial<std::uint32_t>(archive);
  archive.seekg(header_start, std::ifstream::beg);
  std::uint32_t const file_number = read_trivial<std::uint32_t>(archive);
  for (auto i = 0U; i < file_number; ++i) {
    std::int32_t const pos = read_trivial<std::int32_t>(archive);
    std::uint32_t const size = read_trivial<std::uint32_t>(archive);
    std::uint32_t const length = read_trivial<std::uint32_t>(archive);
    std::vector<char> filename_buffer(length + 1);
    archive.read(filename_buffer.data(), length);
    filename_buffer[length] = '\0';
    std::string filename{filename_buffer.data()};
    entities.emplace(filename, entity{pos, size});
  }
}

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cerr << "invalid argument(s). there is a argument that archive file name.\n";
    return 1;
  }
  try {
    std::string const archive_name{argv[1]};
    std::ifstream archive{archive_name, std::ifstream::binary};
    decode_archive(archive);
    for (auto const& m : entities) {
      std::cout << m.first << " " << m.second.position << " " << m.second.size << std::endl;
    }
    auto it = entities.find("archive\\b.txt");
    if (it != entities.end()) {
      auto const& entity = it->second;
      std::vector<char> buffer(entity.size + 1);
      archive.seekg(entity.position, std::ifstream::beg);
      archive.read(buffer.data(), entity.size);
      buffer[entity.size] = '\0';
      std::string const str{buffer.data()};
      std::cout << str << std::endl;
    }
  } catch (fs::filesystem_error const& e) {
    std::cerr << e.what() << " code " << e.code() << std::endl;
  } catch (...) {
    std::cerr << "unknown error\n";
  }
}