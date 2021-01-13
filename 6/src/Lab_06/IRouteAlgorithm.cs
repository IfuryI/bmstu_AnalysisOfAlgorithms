using System;
using System.Collections.Generic;
using System.Text;

namespace Lab_06
{
    public interface IRouteAlgorithm
    {
        public Path GetRoute(Map map);
    }
}
