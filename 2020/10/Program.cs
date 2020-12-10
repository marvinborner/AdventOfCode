using System;
using System.IO;
using System.Linq;

namespace AOC
{
    internal class Run
    {
        private static int PartOne(int[] data)
        {
            int prev = 0, three = 1, one = 0;
            for (int i = 0; i < data.Length; i++)
            {
                if (data[i] - prev == 3) three++;
                else one++;

                prev = data[i];
            }

            return one * three;
        }
        
        private static int PartTwo(int[] data)
        {
            return 0;
        }

        public static void Main(string[] args)
        {
            string text = File.ReadAllText(@"C:\Users\bornerma\Desktop\input.txt");
            string[] numsStr = text.Split('\n');
            int[] nums = Array.ConvertAll(numsStr, int.Parse).OrderBy(i => i).ToArray();
            Console.WriteLine(PartOne(nums));
            Console.WriteLine(PartTwo(nums));
        }
    }
}