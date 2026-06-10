#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <iostream>
#include <fstream>


enum class Direction {
  Up = 0, Down, Left, Right
};

Direction random_direction() {
    static std::random_device rd;  // a seed source for the random number engine
    static std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    static std::uniform_int_distribution<> distrib(0, 7);
    switch (distrib(gen)) {
      // 1/2 chance of up
      case 0: case 1: case 2: case 3: return Direction::Up;
  
      // 1/4 chance of down
      case 4: case 5: return Direction::Down;
  
      // 1/8 chance of left/right
      case 6: return Direction::Left;
      case 7: return Direction::Right;
    }
}

const std::vector<bool>& encode_naive(const Direction d) {
  static std::vector<bool> up    = { 0, 0 };
  static std::vector<bool> down  = { 1, 1 };
  static std::vector<bool> left  = { 1, 0 };
  static std::vector<bool> right = { 0, 1 };
  switch (d) {
    case Direction::Up: return up;
    case Direction::Down: return down;
    case Direction::Left: return left;
    case Direction::Right: return right;
  }
}

const std::vector<bool>& encode_huff(const Direction d) {
  static std::vector<bool> up    = { 0 };
  static std::vector<bool> down  = { 1, 1 };
  static std::vector<bool> left  = { 1, 0, 1 };
  static std::vector<bool> right = { 1, 0, 0 };
  switch (d) {
    case Direction::Up: return up;
    case Direction::Down: return down;
    case Direction::Left: return left;
    case Direction::Right: return right;
  }
}

std::vector<Direction> random_commands(const size_t count) {
  std::vector<Direction> ret;
  ret.reserve(count);
  for (size_t i = 0; i < count; i++)
    ret.emplace_back(random_direction());
  return ret;
}

template<typename Encoder>
std::vector<bool> encode(const std::vector<Direction> directions, Encoder encoder) {
  std::vector<bool> ret;
  for (auto d : directions) {
    const auto& m = encoder(d);
    ret.insert(ret.end(), m.begin(), m.end());
  }
  return ret;
}

template<typename Encoder>
std::vector<bool> random_commands(const size_t count, Encoder encoder) {
  std::vector<bool> ret;
  for (size_t i = 0; i < count; i++) {
    const auto& m = encoder(random_direction());
    ret.insert(ret.end(), m.begin(), m.end());
  }
  return ret;
}

int main(int argc, char** argv) {
  if ( argc < 2 ) {
    std::cerr <<"missing count argument\n";
    return -1;
  }

  auto dirs = random_commands( atoi( argv[1] ) );
  auto naive = encode(dirs, encode_naive);
  auto huff = encode(dirs, encode_huff);
  std::cout <<"naive len: " <<naive.size() <<std::endl;
  std::cout <<"huff len:  " <<huff.size() <<std::endl;

  // Huffman encoded output is smaller even when using external compression algorithms
  // write_to_file(naive, "naive.dat");
  // write_to_file(huff, "huff.dat");
}
