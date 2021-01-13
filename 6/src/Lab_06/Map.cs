using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;

namespace Lab_06
{
    public class Map
    {
        private int[,] dist;
        private readonly Random random;
        public Map(int n, int maxValue = int.MaxValue)
        {
            dist = new int[n, n];
            random = new Random(1);

            for (int i = 0; i < n; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    dist[i, j] = dist[j, i] = random.Next(1, maxValue);
                }
            }
        }

        public Map(string namefile)
        {
            using (var file = new StreamReader(namefile))
            {
                var line = file.ReadLine();
                var data = Regex.Replace(line, "[ ]+", " ").Split();
                dist = new int[data.Length, data.Length];
                for (int i = 0; i < N; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        dist[i, j] = Convert.ToInt32(data[j]);
                    }
                    
                    line = file.ReadLine();
                    if (line != null)
                        data = Regex.Replace(line, "[ ]+", " ").Split();
                }
            }
        }

        public int this[int i, int j]
        {
            get => dist[i, j];
            set => dist[i, j] = value;
        }

        public int N => dist.GetLength(0);

        public override string ToString()
        {
            var stringBuilder = new StringBuilder();
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    stringBuilder.AppendFormat("{0} ", dist[i, j]);
                }
                stringBuilder.Append("\n");
            }
            return stringBuilder.ToString();
        }
    }
}
