// day-12.cpp
// Solution for day 12
#include "utilities.h"
#include <queue>
#include <deque>
#include <unordered_set>

using std::unordered_set;
using std::queue;
using std::deque;

long get_region_price(const Matrix<char>& m, Matrix<bool>& visited, deque<Point>& other_regions, Point start) {
	/*std::cout << "REGION " << m[start] << std::endl;
	std::cout << "---" << std::endl;*/
	
	deque<Point> region;
	region.push_back(start);

	long fences = 0;
	long area = 0;

	while (!region.empty()) {
		Point curr = region.front();
		region.pop_front();

		if (curr.is_within_range(m.rows(), m.cols()) && m[curr] == m[start]) {
			area++;
			visited[curr.x][curr.y] = true;
			
			//std::cout << "Visiting " << curr << ", current area: " << area << std::endl;
			//std::cout << std::endl;

			for (int i = 1; i <= 4; ++i) {
				Point next = curr;
				Direction dir = Direction::all_directions()[i];
				next.move(dir);
				//std::cout << "NEXT " << next << std::endl;

				if (!next.is_within_range(m.rows(), m.cols())) {
					++fences;
					//std::cout << "PERIMETER " << fences << std::endl;
				}
				else if (m[next] == m[start]) {
					if (!visited[next.x][next.y] && 
						find(region.begin(), region.end(), next) == region.end()) {
						region.push_back(next);
						
						//std::cout << "QUEUE " << m[next] << std::endl;
					}
				}
				else {
					++fences;
					//std::cout << "PERIMETER " << fences << std::endl;
					if (!visited[next.x][next.y]) {
						if(find(other_regions.begin(), other_regions.end(), next) == other_regions.end())
							other_regions.push_back(next);
						//std::cout << "Added to other regions " << m[next] << std::endl;
					}
				}
			}
		}
		//std::cout << "---" << std::endl;
	}

	//std::cout << area << " * " << fences << " = " << area * fences << std::endl << std::endl;
	return fences * area;
}

Point wall_between(Point A, Point B) {
	if (A.x == B.x)
		return { A.x, (A.y + B.y) / 2 };

	if (A.y == B.y)
		return { (A.x + B.x) / 2, A.y };

	return { (A.x + B.x) / 2 , (A.y + B.y) / 2 };
}

//long get_region_price2(const Matrix<char>& m, Matrix<bool>& visited, deque<Point>& other_regions, Point start) {
//	/*std::cout << "REGION " << m[start] << std::endl;
//	std::cout << "---" << std::endl;*/
//
//	deque<Point> region;
//	region.push_back(start);
//
//	vector<Point> walls;
//
//	long fences = 0;
//	long area = 0;
//
//	while (!region.empty()) {
//		Point curr = region.front();
//		region.pop_front();
//
//		if (curr.is_within_range(m.rows(), m.cols()) && m[curr] == m[start]) {
//			area++;
//			visited[curr.x][curr.y] = true;
//
//			//std::cout << "Visiting " << curr << ", current area: " << area << std::endl;
//			//std::cout << std::endl;
//
//			for (int i = 1; i <= 4; ++i) {
//				Point next = curr;
//				Direction dir = Direction::all_directions()[i];
//				next.move(dir);
//				//std::cout << "NEXT " << next << std::endl;
//
//				if (!next.is_within_range(m.rows(), m.cols())) {
//					//++fences;
//					//std::cout << "PERIMETER " << fences << std::endl;
//					walls.push_back(wall_between(curr, next));
//				}
//				else if (m[next] == m[start]) {
//					if (!visited[next.x][next.y] &&
//						find(region.begin(), region.end(), next) == region.end()) {
//						region.push_back(next);
//
//						//std::cout << "QUEUE " << m[next] << std::endl;
//					}
//				}
//				else {
//					walls.push_back(wall_between(curr, next));
//					//std::cout << "PERIMETER " << fences << std::endl;
//					if (!visited[next.x][next.y]) {
//						if (find(other_regions.begin(), other_regions.end(), next) == other_regions.end())
//							other_regions.push_back(next);
//						//std::cout << "Added to other regions " << m[next] << std::endl;
//					}
//				}
//			}
//		}
//		//std::cout << "---" << std::endl;
//	}
//
//	unordered_set<double> xs;
//	unordered_set<double> ys;
//	for (auto w : walls) {
//		if(w.x != floor(w.x) || w.x == 0)
//			xs.insert(w.x);
//
//		if (w.y != floor(w.y) || w.y == 0)
//			ys.insert(w.y);
//	}
//
//	fences = xs.size() + ys.size();
//
//	//std::cout << area << " * " << fences << " = " << area * fences << std::endl << std::endl;
//	return fences * area;
//}


long get_fence_price(const Matrix<char>& m) {
	if (m.empty()) return 0;

	Matrix<bool> visited(m.rows(), m.cols(), false);
	deque<Point> region_starts;
	region_starts.push_back(Point());

	long price = 0;

	while (!region_starts.empty()) {
		Point curr = region_starts.front();
		region_starts.pop_front();

		if (curr.is_within_range(m.rows(), m.cols()) && !visited[curr.x][curr.y])
			price += get_region_price2(m, visited, region_starts, curr);
	}

	return price;
}

int main() {
	std::ifstream in = open_file("12-test");
	//std::ifstream in = open_file("12");
	if (!in) return 1;

    Matrix<char> m = input_matrix<char>(in, split_to_chars);
	std::cout << get_fence_price(m) << std::endl;

	in.close();
	return 0;
}