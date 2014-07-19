/**
 * Created by jingx23 on 19.07.14.
 */
import static spark.Spark.*;

public class WeatherApp {
    public static void main(String[] args) {
        get("/hello", (req, res) -> "Hello World");
    }
}
