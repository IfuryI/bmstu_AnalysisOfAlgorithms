using System;
using System.Collections.Generic;
using System.Text;

namespace Lab_06
{
    public class AntsAlgorithm : IRouteAlgorithm
    {
        private readonly Random r = new Random();
        public AntsAlgorithm(int maxTime, double alpha, double beta, double q, double rho)
        {
            MaxTime = maxTime;
            Alpha = alpha;
            Beta = beta;
            Q = q;
            Rho = rho;
        }

        public int MaxTime { get; set; }
        public double Alpha { get; set; }
        public double Beta { get; set; }
        public double Q { get; set; }
        public double Rho { get; set; }

        public static double CalculateQ(Map map)
        {
            double sum = 0;
            for (int i = 0; i < map.N; i++)
            {
                for (int j = i + 1; j < map.N; j++)
                {
                    sum += 2 * map[i, j];
                }
            }
            return sum / map.N;
        }

        public Path GetRoute(Map map)
        {
            Path shortest = new Path(null, map);

            int count = map.N;
            var pher = InitPheromone(count, 0.1);

            for (int time = 0; time < MaxTime; time++)
            {
                var ants = InitAnts(map, map.N);
                for (int i = 0; i < count - 1; i++)
                {
                    double[,] deltaPher = InitPheromone(count, 0);
                    foreach (var ant in ants)
                    {
                        int curTown = ant.LastVisited();

                        double sum = 0;
                        for (int town = 0; town < count; town++)
                        {
                            if (!ant.IsVisited(town))
                            {
                                double tau = pher[curTown, town];
                                double eta = 1 / map[curTown, town];
                                sum += Math.Pow(tau, Alpha) * Math.Pow(eta, Beta);
                            }
                        }

                        double check = r.NextDouble();
                        int newTown = 0;
                        for (; check > 0; newTown++)
                        {
                            if (!ant.IsVisited(newTown))
                            {
                                double tau = pher[curTown, newTown];
                                double eta = 1 / map[curTown, newTown];
                                double chance = Math.Pow(tau, Alpha) * Math.Pow(eta, Beta) / sum;
                                check -= chance;
                            }
                        }
                        newTown--;
                        ant.VisitTown(newTown);
                        deltaPher[curTown, newTown] += Q / map[curTown, newTown];
                    }

                    // Испарение феромонов
                    for (int k = 0; k < count; k++)
                        for (int t = 0; t < count; t++)
                        {
                            pher[k, t] = (1 - Rho) * pher[k, t] + deltaPher[k, t];
                            if (pher[k, t] < 0.1) pher[k, t] = 0.1;
                        }
                }

                // Находим минимальные пути тек. дня
                foreach (var ant in ants)
                {
                    ant.VisitTown(ant.Start);
                    if (ant.GetDistance() < shortest.Distance)
                        shortest = ant.Path;
                }
            }

            return shortest;
        }

        private List<Ant> InitAnts(Map map, int n)
        {
            var ants = new List<Ant>(n);
            for (int i = 0; i < n; i++)
                ants.Add(new Ant(map, 0));
            return ants;
        }

        private double[,] InitPheromone(int size, double num)
        {
            double[,] phen = new double[size, size];
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    phen[i, j] = num;
            return phen;
        }
    }
}
