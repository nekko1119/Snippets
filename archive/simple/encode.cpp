#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <new>
#include <string>
#include <type_traits>
#include <vector>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

std::vector<fs::path> enumerate_files(std::string const& path)
{
  fs::path pt{"archive"};
  std::vector<fs::path> files;
  std::copy(fs::directory_iterator{pt}, fs::directory_iterator{}, std::back_inserter(files));
  return files;
}

std::vector<boost::uintmax_t> enumerate_file_sizes(std::vector<fs::path> const& files)
{
  using size_type = std::vector<fs::path>::size_type;
  size_type const& size = files.size();
  std::vector<boost::uintmax_t> file_sizes(size);
  std::transform(files.begin(), files.end(), file_sizes.begin(), [](fs::path const& file) {
    return fs::file_size(file);
  });
  return file_sizes;
}

void create_body(std::vector<fs::path> const& files, std::vector<boost::uintmax_t> const& file_sizes, std::ofstream& archive)
{
  using size_type = std::vector<fs::path>::size_type;
  size_type const& size = files.size();
  for (auto i = 0U; i < size; ++i) {
    std::ifstream file{files[i].string(), std::ifstream::binary};
    std::vector<char> buffer(static_cast<size_type>(file_sizes[i]));
    file.read(buffer.data(), buffer.size());
    archive.write(buffer.data(), buffer.size());
  }
}

template <class T, std::size_t N = sizeof(T)>
std::enable_if_t<std::is_trivial<T>::value> write_trivial(std::ofstream& ofs, T value)
{
  unsigned char buffer[N];
  new (buffer) T(value);
  ofs.write(reinterpret_cast<char*>(buffer), N);
}

void create_header(std::vector<fs::path> const& files, std::vector<boost::uintmax_t> const& file_sizes, std::ofstream& archive)
{
  std::uint32_t const body_end = static_cast<std::uint32_t>(archive.tellp());
  write_trivial(archive, files.size());
  auto const size = files.size();
  std::int32_t pos = 0;
  for (auto i = 0U; i < size; ++i) {
    write_trivial(archive, pos);
    std::uint32_t s = static_cast<std::uint32_t>(file_sizes[i]);
    write_trivial(archive, s);
    s = static_cast<std::uint32_t>(files[i].string().size());
    write_trivial(archive, s);
    archive.write(files[i].string().c_str(), files[i].string().size());
    pos += static_cast<int>(file_sizes[i]);
  }
  write_trivial(archive, body_end);
}

void create_archive_file(std::vector<fs::path> const& files, std::string const& archive_name)
{
  using size_type = std::vector<fs::path>::size_type;
  auto const file_sizes = enumerate_file_sizes(files);
  std::ofstream archive{archive_name, std::ofstream::binary};
  create_body(files, file_sizes, archive);
  create_header(files, file_sizes, archive);
}

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cerr << "invalid argument(s). there is a argument that archived directory name.\n";
    return 1;
  }
  try {
    auto const& files = enumerate_files(argv[1]);
    std::copy(files.begin(), files.end(), std::ostream_iterator<fs::path>(std::cout, "\n"));
    std::string archive_name{argv[1]};
    archive_name += ".bin";
    create_archive_file(files, archive_name);
  } catch (fs::filesystem_error const& e) {
    std::cerr << e.what() << " code " << e.code() << std::endl;
  } catch (...) {
    std::cerr << "unknown error\n";
  }
}