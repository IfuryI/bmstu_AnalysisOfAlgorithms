using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace Lab_06
{
    public class Path
    {
        private List<int> _path;
        private int _dist;
        private Map _map;

        public Path(List<int> path, Map map)
        {
            _path = path;
            _map = map;
            _dist = GetDistance();
        }

        public Path(Map map, int town)
        {
            _path = new List<int>() { town };
            _map = map;
            _dist = GetDistance();
        }

        public void AddTown(int town)
        {
            _dist += _map[_path.Last(), town];
            _path.Add(town);
        }

        public int LastTown => _path.Last();
        
        public bool CheckTown(int town) => _path.Contains(town);

        public int this[int i] => _path[i];

        public int Distance => _dist;
        private int GetDistance()
        {
            if (_path == null)
                return int.MaxValue;

            int d = 0;
            for (int i = 0; i < _path.Count - 1; i++)
                d += _map[_path[i], _path[i + 1]];
            return d;
        }

        public override string ToString()
        {
            var stringBuilder = new StringBuilder();
            foreach (int num in _path)
                stringBuilder.AppendFormat("{0} ", num);
            return stringBuilder.ToString();
        }
    }
}
