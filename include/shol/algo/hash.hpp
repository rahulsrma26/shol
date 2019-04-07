#pragma once

#include <utility>

namespace shol {

struct CantorHash {
	size_t operator()(const std::pair<int, int>& p) const {
		return (p.first + p.second)*(p.first + p.second + 1) / 2 + p.second;
	}
};

} // namespace shol
