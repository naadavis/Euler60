//Nicholas Davis
//Project Euler 61

#include <iostream>
#include <list>

using namespace std;

int triangle(const int& n) { return (n*(n+1))/2; }
int square(const int& n) { return n*n; }
int pentagonal(const int& n) { return (n*(3*n-1))/2; }
int hexagonal(const int& n) { return (n*(2*n-1)); }
int heptagonal(const int& n) { return (n*(5*n-3))/2; }
int octagonal(const int& n) { return (n*(3*n-2)); }

list<int> fourDigitGen( int (*f)(const int&)  )
{
	int n = 1;
	int k = n;
	list<int> r;
	while( k < 1000 )
	{
		k = f(n++);
	}
	while( k < 10000 )
	{
		r.push_back(k);
		k = f(n++);
	}
	return r;
}

bool match( const int& a, const int& b )
{
	return a%100 == b/100;
}

bool buildCycle( list<int>& path, list<list<int>>& remaining )
{
	/*
	for( auto i = path.begin(); i != path.end(); ++i )
	{
		cout << " -> " << *i;
	}
	cout << endl;
	*/
	for( auto i = remaining.begin(); i != remaining.end(); ++i )
	{
		for( auto& n : (*i) )
		{
			if( path.size() < 5 )
			{
				if( match( n, path.front() ) )
				{
					path.push_front(n);
					list<list<int>> tmp;
					for( auto j = remaining.begin(); j != remaining.end(); ++j )
					{
						if( j != i ) tmp.push_back(*j);
					}
					if( buildCycle(path,tmp) )
					{
						return true;
					}
					else
					{
						path.pop_front();
					}
				}
				if( match( path.back(), n ) )
				{
					path.push_back(n);
					list<list<int>> tmp;
					for( auto j = remaining.begin(); j != remaining.end(); ++j )
					{
						if( j != i ) tmp.push_back(*j);
					}
					if( buildCycle(path,tmp) )
					{
						return true;
					}
					else
					{
						path.pop_back();
					}
				}
			}
			else
			{
				if( match(n,path.front()) && match(path.back(),n) )
				{
					// found the cycle
					auto sum = n;
					cout << n;
					for( auto &i : path )
					{
						cout << " -> " << i;
						sum += i;
					}
					cout << endl << sum << endl;
					return true;
				}
			}
		}
	}
	return false;
}

int main()
{
	list<list<int>> ftypes;
	ftypes.push_back( fourDigitGen( &heptagonal ) );
	ftypes.push_back( fourDigitGen( &triangle ) );
	ftypes.push_back( fourDigitGen( &square ) );
	ftypes.push_back( fourDigitGen( &square ) );
	ftypes.push_back( fourDigitGen( &pentagonal ) );
	ftypes.push_back( fourDigitGen( &hexagonal ) );
	/*
 	figfuncs[1] = heptagonal;
	figfuncs[2] = triangle;
	figfuncs[3] = square;
	figfuncs[4] = pentagonal;
	figfuncs[5] = hexagonal;
	*/
	for( auto &n : fourDigitGen( &octagonal ) )
	{
		list<int> temp(1,n);
		if( buildCycle(temp,ftypes) ) return 0;
		//cout << n << " didn't work" <<endl;
	}
	return 0;
}
