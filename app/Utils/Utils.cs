namespace Utils
{
    public class Utils
    {
        public static void UpdateArray(double value, List<double> data)
        {
            if (data.Count >= 50)
                data.RemoveAt(0);

            data.Add(value);
        }   
    }
}