struct Rocket
{
	int numEqns;
	double s;
	double q[10];

	int numberOfEngines;
	int seaLevelThrustPerEngine;
	double vacuumThrustPerEngine;
	double rocketDiameter;
	double cd;
	double initialMass;
	double burnTime;
};

struct RocketSimModel
{
	double x;
	double z;
	double v;
	double time;
	double mass;
	double dt;
	double pi;
	struct Rocket rocket;
};

struct USatm76
{
	double pressure;
	double density;
	double temperature;
};

class RocketModel
{
	private:
	public:
		static void rocketRightHandSide(
			struct Rocket *rocket,
			double *q,
			double *deltaQ,
			double ds,
			double qScale,
			double *dq
		);
		static void rocketRungeKutta4(
			struct Rocket *rocket,
			double ds
		);
		static void updateConditions(
			struct USatm76 *air,
			double altitude
		);
		static struct RocketSimModel SetSimModel();
};