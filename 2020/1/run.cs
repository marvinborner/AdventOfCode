using System;
using System.IO;
using System.Linq;

namespace AOC
{
    internal class Run
    {
        private static int[] Double(int[] arr, int low, int result)
        {
            int high = arr.Length - 1;

            int sum = arr[low] + arr[high];
            while (low < high && sum != result)
            {
                if (sum < result)
                    low++;
                else
                    high--;

                sum = arr[low] + arr[high];
            }

            if (low == high)
            {
                return new[] {0, 0};
            }

            return new[] {arr[low], arr[high]};
        }

        private static int[] Triple(int[] arr, int result)
        {
            for (int i = 0; i < arr.Length; i++)
            {
                int remainder = result - arr[i];
                int[] d = Double(arr, i, remainder);
                if (d.Sum() != 0)
                {
                    return new[] {arr[i], d[0], d[1]};
                }
            }

            return new[] {0, 0};
        }

        public static void Main(string[] args)
        {
            string text = File.ReadAllText("input");
            string[] numsStr = text.Split('\n');
            numsStr[numsStr.Length - 1] = "2020"; // Some weird newline character ig
            int[] nums = Array.ConvertAll(numsStr, int.Parse).OrderBy(i => i).ToArray();
            int[] d = Double(nums, 0, 2020);
            int[] t = Triple(nums, 2020);
            Console.WriteLine(d[0] * d[1]);
            Console.WriteLine(t[0] * t[1] * t[2]);
        }
    }
}
