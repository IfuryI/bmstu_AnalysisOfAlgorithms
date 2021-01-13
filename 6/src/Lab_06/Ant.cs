using System;
using System.Collections.Generic;
using System.Text;

namespace Lab_06
{
    internal class Ant
    {
        private Path _path;
        private int _town;

        public Ant(Map map, int town)
        {
            _path = new Path(map, town);
            _town = town;
        }

        public void VisitTown(int town) => _path.AddTown(town);
        public int LastVisited() => _path.LastTown;
        public bool IsVisited(int town) => _path.CheckTown(town);
        public int GetDistance() => _path.Distance;
        public Path Path => _path;
        public int Start => _town;
    }
}
