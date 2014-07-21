// This #include statement was automatically added by the Spark IDE.
#include "idDHT22/idDHT22.h"


// declaration for DHT11 handler
int idDHT22pin = D0; //Digital pin for comunications
void dht22_wrapper(); // must be declared before the lib initialization

// DHT instantiate
idDHT22 DHT22(idDHT22pin, dht22_wrapper);

char weatherData [700];
char messageType [5];
char message [100];
void setup()
{
    Spark.variable("weather", &weatherData, STRING);
}
// This wrapper is in charge of calling
// mus be defined like this for the lib work
void dht22_wrapper() {
	DHT22.isrCallback();
}
void loop()
{
	delay(100);
	DHT22.acquire();
	while (DHT22.acquiring())
		;
	int result = DHT22.getStatus();
		switch (result)
	{
		case IDDHTLIB_OK:
            sprintf(messageType,"OK");
		    sprintf(message, "");
			break;
		case IDDHTLIB_ERROR_CHECKSUM:
            sprintf(messageType,"ERROR");
		    sprintf(message, "Checksum error");
			break;
		case IDDHTLIB_ERROR_ISR_TIMEOUT:
		    sprintf(messageType,"ERROR");
		    sprintf(message, "ISR Time out error");
			break;
		case IDDHTLIB_ERROR_RESPONSE_TIMEOUT:
            sprintf(messageType,"ERROR");
		    sprintf(message, "Response time out error");
			break;
		case IDDHTLIB_ERROR_DATA_TIMEOUT:
			sprintf(messageType,"ERROR");
		    sprintf(message, "Error Data time out error");
			break;
		case IDDHTLIB_ERROR_ACQUIRING:
			sprintf(messageType,"ERROR");
		    sprintf(message, "Error Acquiring");
			break;
		case IDDHTLIB_ERROR_DELTA:
		    sprintf(messageType,"ERROR");
		    sprintf(message, "Error Delta time to small");
			break;
		case IDDHTLIB_ERROR_NOTSTARTED:
		    sprintf(messageType,"ERROR");
		    sprintf(message, "Not started");
			break;
		default:
			sprintf(messageType,"ERROR");
		    sprintf(message, "Unknown error");
			break;
	}
    sprintf(weatherData,"{\"temperature\": %.1f, \"humidity\": %.1f, \"dewPoint\": %.1f, \"dewPointSlow\": %.1f, \"messageType\": %s, \"message\": %s}", DHT22.getCelsius(), DHT22.getHumidity(), DHT22.getDewPoint(), DHT22.getDewPointSlow(), messageType, message);
    delay(2000);
}