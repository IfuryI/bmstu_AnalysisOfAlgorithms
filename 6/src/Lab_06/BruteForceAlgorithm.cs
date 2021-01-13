using System;
using System.Collections.Generic;
using System.Text;

namespace Lab_06
{
    public class BruteForceAlgorithm : IRouteAlgorithm
    {
        public Path GetRoute(Map map)
        {
            Path shortest = new Path(null, map);
            foreach (var cur in GetAllRoutes(map.N))
            {
                cur.Add(cur[0]);
                Path check = new Path(cur, map);
                if (shortest.Distance > check.Distance)
                    shortest = check;
            }
            return shortest;
        }

        private IEnumerable<List<int>> GetAllRoutes(int count)
        {
            List<int> cur = new List<int>();
            for (int i = 0; i < count; i++)
                cur.Add(i);

            yield return new List<int>(cur);
            while (NextSet(cur, count))
                yield return new List<int>(cur);
        }

        private bool NextSet(List<int> cur, int count)
        {
            int j = count - 2;
            while (j != -1 && cur[j] >= cur[j + 1]) 
                j--;

            if (j == -1 || cur[j] == 0)
                return false;

            int k = count - 1;
            while (cur[j] >= cur[k])
                k--;
            Swap(cur, j, k);
            int left = j + 1;
            int right = count - 1;

            while (left < right)
                Swap(cur, left++, right--);
            return true;
        }

        private void Swap(List<int> cur, int i, int j)
        {
            int tmp = cur[i];
            cur[i] = cur[j];
            cur[j] = tmp;
        }
    }
}
