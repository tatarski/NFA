template <class T1, class T2>
struct Pair {
public:
	T1 first;
	T2 second;

	Pair(T1 first = T1(), T2 second = T2()) {
		this->first = first;
		this->second = second;
	}
	bool operator==(Pair<T1, T2> other) {
		return this->first == other.first && this->second == other.second;
	}
};