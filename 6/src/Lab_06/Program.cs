using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace Lab_06
{
    class Program
    {
        static List<AntsAlgorithm> GetAntsAlgorithms(Map map)
        {
            var routeAlgorithms = new List<AntsAlgorithm>();
            double q = AntsAlgorithm.CalculateQ(map);
            routeAlgorithms.Add(new AntsAlgorithm(1000, 0.1, 0.9, q, 0));

            for (double alpha = 0; alpha < 1; alpha += 0.1)
            {
                for (double beta = 0; beta < 1; beta += 0.1)
                {
                    for (double rho = 0; rho < 1; rho += 0.25)
                    {
                        routeAlgorithms.Add(new AntsAlgorithm(30, alpha, beta, q, rho));
                    }
                }
            }

            return routeAlgorithms;
        }

        static void Test()
        {
            var map = new Map(9, 10);
            Console.WriteLine(map);

            var bruteForce = new BruteForceAlgorithm();
            var shortestPath = bruteForce.GetRoute(map);
            var shortestDistance = shortestPath.Distance;

            foreach (var antsAlgorithm in GetAntsAlgorithms(map))
            {
                var path = antsAlgorithm.GetRoute(map);
                var diff = path.Distance - shortestDistance;
                if (diff < 7)
                {
                    Console.WriteLine("{1,-5:0.0} {2,-5:0.0} {3,-5:0.0} {4,-5:0.0} {5}",
                        antsAlgorithm.MaxTime,
                        antsAlgorithm.Alpha,
                        antsAlgorithm.Beta,
                        antsAlgorithm.Q,
                        antsAlgorithm.Rho,
                        diff);
                }
            }
        }

        static void Main(string[] args)
        {
            //Map(@"C:\Users\mad-m\source\repos\BMSTU\AnalysisAlgorithms\Lab_06\src\Lab_06\data\map1.txt");
            var map = new Map(9, 10);
            Console.WriteLine(map);

            var routeAlgorithms = new List<IRouteAlgorithm>();
            routeAlgorithms.Add(new BruteForceAlgorithm());
            routeAlgorithms.Add(new AntsAlgorithm(30, 1, 0, AntsAlgorithm.CalculateQ(map), 0.5));
            foreach (var routeAlgorithm in routeAlgorithms)
            {
                var res = routeAlgorithm.GetRoute(map);
                Console.WriteLine(routeAlgorithm.GetType().Name);
                Console.WriteLine("Path: {0}", res);
                Console.WriteLine("Distance: {0}", res.Distance);
                Console.WriteLine();
            }
            Console.WriteLine();

            int samples = 1;
            var clock = new Stopwatch();
            foreach (var routeAlgorithm in routeAlgorithms)
            {
                clock.Restart();
                for (int i = 0; i < samples; i++)
                {
                    clock.Start();
                    routeAlgorithm.GetRoute(map);
                    clock.Stop();
                }
                var avgTime = clock.ElapsedTicks / (double)samples;
                Console.WriteLine($"{routeAlgorithm.GetType().Name,-20} time work: {avgTime} ticks");
            }

            Test();
        }
    }
}
