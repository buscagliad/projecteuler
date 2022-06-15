#include <cstdlib>
#include <cstdio>

class hist {
	public:
		hist(int _smallest_bin, int _largest_bin);
		~hist();
		void	add(int value);
		void	clear();
		bool	most(int &value, int &count);
		int		get(int b) {
			if (b < smallest) return too_small_cnt;
			else if (b > largest) return too_large_cnt;
			return bin[b];;
		}
		void    out(const char *text = "");
	private:
		
        int     smallest;       /* smallest value in histogram */
        int     largest;        /* largest value in histogram */
        int     bin_count;      /* total number of bins */
        int     too_small_cnt;  /* number of too small elements attempted to be added */
        int     too_large_cnt;  /* number of too large elements attempted to be added */
		int		big_bin;
        int     *bin;          /* array of bins */
};

inline
void hist::out(const char *text)
{
	printf("%s\n", text);
	printf(" %4d < ", too_small_cnt);
	for (int i = 0; i < bin_count; i++) printf("%5d ", bin[i]);
	printf(" < %4d\n", too_large_cnt);
	printf("        ");
	for (int i = smallest; i <= largest; i++) printf("%5d ", i);
	printf("\n");
}

inline
void hist::clear()
{
	too_small_cnt = 0;
	too_large_cnt = 0;
	big_bin = -1;
	for (int i = 0; i < bin_count; i++) bin[i] = 0;
}

inline
hist::hist(int sb, int lb)
{
	smallest = sb;
	largest = lb;
	bin_count = lb - sb + 1;
	bin = (int *) malloc (bin_count * sizeof(int));
	clear();
}

inline
void	hist::add(int v)
{
	if (v < smallest) 
		too_small_cnt++;
	else if (v > largest) 
		too_large_cnt++;
	else
	{
		bin[v - smallest]++;
		if (big_bin < 0) big_bin = v - smallest;
		else if (bin[v - smallest] > bin[big_bin]) big_bin = v - smallest;
	}
}

inline
bool	hist::most(int &value, int &count)
{
	count = bin[big_bin];
	value = big_bin + smallest;
	return true;
}

inline
hist::~hist() {
	free(bin);
}
