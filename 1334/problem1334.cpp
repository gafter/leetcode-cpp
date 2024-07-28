#include <vector>
#include <cassert>

using namespace std;

/**
 * There are n cities numbered from 0 to n-1. Given the array edges where
 * edges[i] = [fromi, toi, weighti] represents a bidirectional and weighted
 * edge between cities fromi and toi, and given the integer distanceThreshold.
 *
 * Return the city with the smallest number of cities that are reachable
 * through some path and whose distance is at most distanceThreshold,
 * If there are multiple such cities, return the city with the greatest number.
 *
 * Notice that the distance of a path connecting cities i and j is equal to
 * the sum of the edges' weights along that path.
 */
class Solution
{
public:
    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold)
    {
        // create a matrix of distances.
        uint minpath[n][n];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                minpath[i][j] = (i == j) ? 0 : INT_MAX;
        }

        // populate the matrix of distances from the edges
        for (const vector<int> edge : edges)
        {
            int from = edge[0];
            int to = edge[1];
            int len = edge[2];
            minpath[from][to] = minpath[to][from] = len;
        }

        // using dynamic programming, compute the minimum cost along
        // ever-increasing path lengths.
        for (int l = 1; l < n; l *= 2)
        {
            bool changed = false;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                    if (j != i)
                    {
                        uint oldcost = minpath[i][j];
                        uint cost = oldcost;
                        for (int k = 0; k < n; k++)
                            if (k != i && k != j)
                            {
                                uint c = minpath[i][k] + minpath[k][j];
                                if (c < cost)
                                    cost = c;
                            }
                        if (cost < oldcost)
                        {
                            minpath[i][j] = minpath[j][i] = cost;
                            changed = true;
                        }
                    }
            }
            if (!changed)
                break;
        }

        int res = -1;
        int num = INT_MAX;

        for (int candidate = 0; candidate < n; candidate++)
        {
            int cnum = 0;
            for (int neighbor = 0; neighbor < n; neighbor++)
            {
                if (minpath[candidate][neighbor] <= distanceThreshold)
                    cnum++;
            }
            if (cnum <= num)
            {
                res = candidate;
                num = cnum;
            }
        }

        return res;
    }
};
