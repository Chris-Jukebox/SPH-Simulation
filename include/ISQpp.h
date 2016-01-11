/*
* Copyright © 2015 Jeremy T. Hatcher All Rights Reserved
*/

/*
* 
* ISQpp.h
*
* International System of Quantities
* 
* @author Jeremy T. Hatcher
* @date 07/27/2015
* @version 1.1
*
*/

#ifndef ISQPP_H
#define ISQPP_H

#include <cmath>
#include <limits>

namespace si
{


	/*
	* exponent tables
	* (length, mass, time, current, temperature, amount, intensity)
	*/

	//base units
#define ISQ_baseMetaArgs_LENG 1,0,0,0,0,0,0 //length
#define ISQ_baseMetaArgs_MASS 0,1,0,0,0,0,0 //mass
#define ISQ_baseMetaArgs_TIME 0,0,1,0,0,0,0 //time
#define ISQ_baseMetaArgs_CURR 0,0,0,1,0,0,0 //current
#define ISQ_baseMetaArgs_TEMP 0,0,0,0,1,0,0 //temperature
#define ISQ_baseMetaArgs_AMTS 0,0,0,0,0,1,0 //amount of substance
#define ISQ_baseMetaArgs_INTS 0,0,0,0,0,0,1 //intensity

	//derived units
#define ISQ_baseMetaArgs_AREA 2,0,0,0,0,0,0 //area
#define ISQ_baseMetaArgs_VOLM 3,0,0,0,0,0,0 //volume
#define ISQ_baseMetaArgs_VELO 1,0,-1,0,0,0,0 //velocity
#define ISQ_baseMetaArgs_ACCL 1,0,-2,0,0,0,0 //acceleration
#define ISQ_baseMetaArgs_JOLT 1,0,-3,0,0,0,0 //jolt
#define ISQ_baseMetaArgs_ANGV 0,0,-1,0,0,0,0 //angular velocity
#define ISQ_baseMetaArgs_MOMT 1,1,-1,0,0,0,0 //momentum
#define ISQ_baseMetaArgs_ANGM 2,1,-1,0,0,0,0 //angular momentum
#define ISQ_baseMetaArgs_TORQ 2,1,-2,0,0,0,0 //torque
#define ISQ_baseMetaArgs_ARDN -2,1,0,0,0,0,0 //area density
#define ISQ_baseMetaArgs_DENS -3,1,0,0,0,0,0 //density
#define ISQ_baseMetaArgs_SVOL 3,-1,0,0,0,0,0 //specific volume

#define ISQ_baseMetaArgs_HCAP 2,1,-2,0,-1,0,0 //heat capacity
#define ISQ_baseMetaArgs_MHCP 2,1,-2,0,-1,-1,0 //molar heat capacity
#define ISQ_baseMetaArgs_SHCP 2,0,-2,0,-1,0,0 //specific heat capacity

#define ISQ_baseMetaArgs_SENG 2,0,-2,0,0,0,0 //specific energy
#define ISQ_baseMetaArgs_ENDN -1,1,-2,0,0,0,0 //energy density
#define ISQ_baseMetaArgs_STNS 0,1,-2,0,0,0,0 //surface tension
#define ISQ_baseMetaArgs_HFLX 0,1,-3,0,0,0,0 //heat flux
#define ISQ_baseMetaArgs_TCON 1,1,-3,0,-1,0,0 //thermal conductivity
#define ISQ_baseMetaArgs_KVIS 2,0,-1,0,0,0,0 //kinematic viscosity
#define ISQ_baseMetaArgs_DVIS -1,1,-1,0,0,0,0 //dynamic viscosity

#define ISQ_baseMetaArgs_HRTZ 0,0,-1,0,0,0,0 //frequency
#define ISQ_baseMetaArgs_WLEN 1,0,0,0,0,0,0 //wavelength
#define ISQ_baseMetaArgs_WNUM -1,0,0,0,0,0,0 //wavenumber
#define ISQ_baseMetaArgs_FORC 1,1,-2,0,0,0,0 //force
#define ISQ_baseMetaArgs_IMPU 1,1,-1,0,0,0,0 //impulse
#define ISQ_baseMetaArgs_PRES -1,1,-2,0,0,0,0 //pressure
#define ISQ_baseMetaArgs_ENRG 2,1,-2,0,0,0,0 //energy
#define ISQ_baseMetaArgs_WORK 2,1,-2,0,0,0,0 //work
#define ISQ_baseMetaArgs_POWR 2,1,-3,0,0,0,0 //power
#define ISQ_baseMetaArgs_CHRG 0,0,1,1,0,0,0 //charge
#define ISQ_baseMetaArgs_VOLT 2,1,-3,-1,0,0,0 //voltage
#define ISQ_baseMetaArgs_ECAP -1,-1,4,2,0,0,0 //electrical capacitance
#define ISQ_baseMetaArgs_ERES 2,1,-3,-2,0,0,0 //electrical resistance
#define ISQ_baseMetaArgs_ECON -2,-1,3,-1,0,0,0 //electrical conductivity
#define ISQ_baseMetaArgs_MFLX 2,1,-2,-1,0,0,0 //magnetic flux
#define ISQ_baseMetaArgs_INDC 2,1,-2,-2,0,0,0 //
#define ISQ_baseMetaArgs_LFLX 0,0,0,0,0,0,1 //luminous flux
#define ISQ_baseMetaArgs_ILLM -2,0,0,0,0,0,1 //luminance
#define ISQ_baseMetaArgs_RDAC 0,0,-1,0,0,0,0 //radioactivity
#define ISQ_baseMetaArgs_RDAD 2,0,-2,0,0,0,0 //absorbed radioactive dose
#define ISQ_baseMetaArgs_RDED 2,0,-2,0,0,0,0 //equivalent radioactive dose
#define ISQ_baseMetaArgs_CATA 0,0,-1,0,0,1,0 //catalytic activity

#define ISQ_baseMetaArgs_GENR 0,0,0,0,0,0,0 //dimensionless generic
#define ISQ_baseMetaArgs_DLES 0,0,0,0,0,0,0 //dimensionless scalar

	//template argument lists
#define ISQ_metaArgsMultiplication \
le+LE, ma+MA, ti+TI, cu+CU, te+TE, am+AM, in+IN

#define ISQ_metaArgsDivision \
le-LE, ma-MA, ti-TI, cu-CU, te-TE, am-AM, in-IN

#define ISQ_metaArgsComboList \
le, LE, ma, MA, ti, TI, cu, CU, te, TE, am, AM, in, IN

#define ISQ_metaArgsList \
le, ma, ti, cu, te, am, in

#define ISQ_metaArgsSecondaryList \
LE, MA, TI, CU, TE, AM, IN

#define ISQ_metaArgsComboDefinition \
int le, int ma, int ti, int cu, int te, int am, int in, int LE, int MA, int TI, int CU, int TE, int AM, int IN

#define ISQ_metaArgsDefinition \
int le, int ma, int ti, int cu, int te, int am, int in

#define ISQ_metaArgsSecondaryDefinition \
int LE, int MA, int TI, int CU, int TE, int AM, int IN

	namespace isq_internal
	{
		struct generic_scalar {};

		template<typename T_dim> class impl_vector2;
		template<typename T_dim> class impl_vector3;
		template<typename T_dim> class impl_vectorP;
	}

	template <ISQ_metaArgsDefinition>
	struct isq_base0;

	template <ISQ_metaArgsDefinition>
	const isq_base0<ISQ_metaArgsList>
		operator+(const isq_base0<ISQ_metaArgsList>&);

	template <ISQ_metaArgsDefinition>
	const isq_base0<ISQ_metaArgsList>
		operator-(const isq_base0<ISQ_metaArgsList>&);


	template <ISQ_metaArgsDefinition>
	struct isq_base0 : isq_internal::generic_scalar
	{
		isq_base0(double _in = 0.0) :value(_in) {}

		template<ISQ_metaArgsSecondaryDefinition>
		isq_base0(isq_base0<ISQ_metaArgsSecondaryList> _in) : value(_in.value) {}

		//operator int() const { return (int)value; }
		//operator float() const { return (float)value; }
		operator double() const { return value; }

		/// euclidean distance constructor
		isq_base0(const isq_internal::impl_vector2<isq_base0<ISQ_metaArgsList>>& lhs,
			const isq_internal::impl_vector2<isq_base0<ISQ_metaArgsList>>& rhs);

		/// operator+=(isq_base0, isq_base0)
		isq_base0& operator+=(const isq_base0 rhs) {
			value += rhs.value;
			return *this;
		}
		/// operator-=(isq_base0, isq_base0)
		isq_base0& operator-=(const isq_base0 rhs) {
			value -= rhs.value;
			return *this;
		}

		double value;
	};

	/// euclidean distance constructor
	template<ISQ_metaArgsDefinition>
	isq_base0<ISQ_metaArgsList>::isq_base0(
		const isq_internal::impl_vector2<isq_base0<ISQ_metaArgsList>>& lhs,
		const isq_internal::impl_vector2<isq_base0<ISQ_metaArgsList>>& rhs) {
		isq_base0<ISQ_metaArgsList> d1 = (rhs.x - lhs.x);
		isq_base0<ISQ_metaArgsList> d2 = (rhs.y - lhs.y);
		value = std::sqrt((d1.value*d1.value) + (d2.value*d2.value));
	}

	/// operator+(isq_base0, isq_base0)
	template
		<ISQ_metaArgsDefinition>
		const isq_base0<ISQ_metaArgsList>
		operator+(const isq_base0<ISQ_metaArgsList>& lhs,
			const isq_base0<ISQ_metaArgsList>& rhs)
	{
		return isq_base0<ISQ_metaArgsList>(lhs) += rhs;
	}

	/// operator-(isq_base0, isq_base0)
	template
		<ISQ_metaArgsDefinition>
		const isq_base0<ISQ_metaArgsList>
		operator-(const isq_base0<ISQ_metaArgsList>& lhs,
			const isq_base0<ISQ_metaArgsList>& rhs)
	{
		return isq_base0<ISQ_metaArgsList>(lhs) -= rhs;
	}

	/// operator*(isq_base0, isq_base0)
	template
		<ISQ_metaArgsComboDefinition>
		isq_base0<ISQ_metaArgsMultiplication>
		operator*(const isq_base0<ISQ_metaArgsList>& lhs,
			const isq_base0<ISQ_metaArgsSecondaryList>& rhs)
	{
		return isq_base0<ISQ_metaArgsMultiplication>
			(lhs.value*rhs.value);
	}

	/// operator*(double, isq_base0)
	template
		<ISQ_metaArgsDefinition>
		isq_base0<ISQ_metaArgsList>
		operator*(const double& lhs, const isq_base0<ISQ_metaArgsList>& rhs)
	{
		return isq_base0<ISQ_metaArgsList>
			(lhs*rhs.value);
	}

	/// operator/(isq_base0, isq_base0)
	template
		<ISQ_metaArgsComboDefinition>
		isq_base0<ISQ_metaArgsDivision>
		operator/(const isq_base0<ISQ_metaArgsList>& lhs,
			const isq_base0<ISQ_metaArgsSecondaryList>& rhs)
	{
		return isq_base0<ISQ_metaArgsDivision>
			(lhs.value / rhs.value);
	}

	/// operator==(isq_base0, isq_base0)
	template
		<ISQ_metaArgsDefinition>
		bool operator==(const isq_base0<ISQ_metaArgsList>& lhs,
			const isq_base0<ISQ_metaArgsList>& rhs)
	{
		return std::fabs(lhs - rhs) < std::numeric_limits<double>::epsilon();
	}

	/// operator!=(isq_base0, isq_base0)
	template
		<ISQ_metaArgsDefinition>
		bool operator!=(const isq_base0<ISQ_metaArgsList>& lhs,
			const isq_base0<ISQ_metaArgsList>& rhs)
	{
		return !(std::fabs(lhs - rhs) < std::numeric_limits<double>::epsilon());
	}

	/// operator<=(isq_base0, isq_base0)
	template
		<ISQ_metaArgsDefinition>
		bool
		operator<=(const isq_base0<ISQ_metaArgsList>& lhs,
			const isq_base0<ISQ_metaArgsList>& rhs)
	{
		return (lhs.value < rhs.value) || (std::fabs(lhs - rhs) < std::numeric_limits<double>::epsilon());
	}

	/// operator>=(isq_base0, isq_base0)
	template
		<ISQ_metaArgsDefinition>
		bool
		operator>=(const isq_base0<ISQ_metaArgsList>& lhs,
			const isq_base0<ISQ_metaArgsList>& rhs)
	{
		return (lhs.value > rhs.value) || (std::fabs(lhs - rhs) < std::numeric_limits<double>::epsilon());
	}

	/// operator<(isq_base0, isq_base0)
	template
		<ISQ_metaArgsDefinition>
		bool
		operator<(const isq_base0<ISQ_metaArgsList>& lhs,
			const isq_base0<ISQ_metaArgsList>& rhs)
	{
		return lhs.value < rhs.value;
	}

	/// operator>(isq_base0, isq_base0)
	template
		<ISQ_metaArgsDefinition>
		bool
		operator>(const isq_base0<ISQ_metaArgsList>& lhs,
			const isq_base0<ISQ_metaArgsList>& rhs)
	{
		return lhs.value > rhs.value;
	}

	///base units
	typedef isq_base0<ISQ_baseMetaArgs_LENG> length;
	typedef isq_base0<ISQ_baseMetaArgs_MASS> mass;
	typedef isq_base0<ISQ_baseMetaArgs_TIME> time;
	typedef isq_base0<ISQ_baseMetaArgs_CURR> current;
	typedef isq_base0<ISQ_baseMetaArgs_TEMP> temperature;
	typedef isq_base0<ISQ_baseMetaArgs_AMTS> amount;
	typedef isq_base0<ISQ_baseMetaArgs_INTS> intensity;

	///derived units
	typedef isq_base0<ISQ_baseMetaArgs_DLES> angle; //radians
	typedef isq_base0<ISQ_baseMetaArgs_AREA> area;
	typedef isq_base0<ISQ_baseMetaArgs_VOLM> volume;
	typedef isq_base0<ISQ_baseMetaArgs_VELO> velocity;
	typedef isq_base0<ISQ_baseMetaArgs_ACCL> acceleration;
	typedef isq_base0<ISQ_baseMetaArgs_JOLT> jolt;
	typedef isq_base0<ISQ_baseMetaArgs_ANGV> angular_velocity;
	typedef isq_base0<ISQ_baseMetaArgs_MOMT> momentum;
	typedef isq_base0<ISQ_baseMetaArgs_ANGM> angular_momentum;
	typedef isq_base0<ISQ_baseMetaArgs_TORQ> torque;
	typedef isq_base0<ISQ_baseMetaArgs_ARDN> area_density;
	typedef isq_base0<ISQ_baseMetaArgs_DENS> density;
	typedef isq_base0<ISQ_baseMetaArgs_SVOL> specific_volume;
	typedef isq_base0<ISQ_baseMetaArgs_HCAP> heat_capacity;
	typedef isq_base0<ISQ_baseMetaArgs_MHCP> molar_heat_capacity;
	typedef isq_base0<ISQ_baseMetaArgs_SHCP> specific_heat_capacity;
	typedef isq_base0<ISQ_baseMetaArgs_SENG> specific_energy;
	typedef isq_base0<ISQ_baseMetaArgs_ENDN> energy_density;
	typedef isq_base0<ISQ_baseMetaArgs_STNS> surface_tension;
	typedef isq_base0<ISQ_baseMetaArgs_HFLX> heatflux;
	typedef isq_base0<ISQ_baseMetaArgs_TCON> thermal_conductivity;
	typedef isq_base0<ISQ_baseMetaArgs_KVIS> kinetic_viscosity;
	typedef isq_base0<ISQ_baseMetaArgs_DVIS> dynamic_viscosity;
	typedef isq_base0<ISQ_baseMetaArgs_HRTZ> frequency;
	typedef isq_base0<ISQ_baseMetaArgs_WLEN> wavelength;
	typedef isq_base0<ISQ_baseMetaArgs_WNUM> wavenumber;
	typedef isq_base0<ISQ_baseMetaArgs_FORC> force;
	typedef isq_base0<ISQ_baseMetaArgs_IMPU> impulse;
	typedef isq_base0<ISQ_baseMetaArgs_PRES> pressure;
	typedef isq_base0<ISQ_baseMetaArgs_ENRG> energy;
	typedef isq_base0<ISQ_baseMetaArgs_WORK> work;
	typedef isq_base0<ISQ_baseMetaArgs_POWR> power;
	typedef isq_base0<ISQ_baseMetaArgs_CHRG> charge;
	typedef isq_base0<ISQ_baseMetaArgs_VOLT> voltage;
	typedef isq_base0<ISQ_baseMetaArgs_ECAP> capacitance;
	typedef isq_base0<ISQ_baseMetaArgs_ERES> resistance;
	typedef isq_base0<ISQ_baseMetaArgs_ECON> conductivity;
	typedef isq_base0<ISQ_baseMetaArgs_MFLX> magneticflux;
	typedef isq_base0<ISQ_baseMetaArgs_LFLX> luminousflux;
	typedef isq_base0<ISQ_baseMetaArgs_ILLM> illuminance;
	typedef isq_base0<ISQ_baseMetaArgs_RDAC> radioactivity;
	typedef isq_base0<ISQ_baseMetaArgs_RDAD> absorbed_rad_dose;
	typedef isq_base0<ISQ_baseMetaArgs_RDED> equivalent_rad_dose;
	typedef isq_base0<ISQ_baseMetaArgs_CATA> catalytic_activity;

	typedef isq_base0<ISQ_baseMetaArgs_DLES> dimensionless;


	namespace isq_internal
	{
		/***********/
		/**VECTOR2**/
		/***********/
		template<typename T_dim>
		class impl_vector2
		{
		public:
			impl_vector2(T_dim _x = 0, T_dim _y = 0) : x(_x), y(_y) {};
			impl_vector2<T_dim> operator=(const impl_vector2<T_dim> rhs) {
				this->x = rhs.x;
				this->y = rhs.y;
				return *this;
			};

			operator impl_vectorP<T_dim>() const {
				T_dim M = std::sqrt((x*x) + (y*y));
				si::angle th = atan2(x, y);
				return impl_vectorP<T_dim>(M, th);
			}

			T_dim x;
			T_dim y;
		};

		/**ADDITION**/
		template<ISQ_metaArgsDefinition>
		inline impl_vector2<isq_base0<ISQ_metaArgsList>>
			operator+(const impl_vector2<isq_base0<ISQ_metaArgsList>>& lhs, const impl_vector2<isq_base0<ISQ_metaArgsList>>& rhs) {
			return impl_vector2<isq_base0<ISQ_metaArgsList>>(lhs.x + rhs.x, lhs.y + rhs.y);
		}
		template<ISQ_metaArgsDefinition>
		inline void operator+=(impl_vector2<isq_base0<ISQ_metaArgsList>>& lhs, const impl_vector2<isq_base0<ISQ_metaArgsList>>& rhs) {
			lhs = (lhs + rhs);
		}

		/**SUBTRACTION**/
		template<ISQ_metaArgsDefinition>
		inline impl_vector2<isq_base0<ISQ_metaArgsList>>
			operator-(const impl_vector2<isq_base0<ISQ_metaArgsList>>& lhs,
				const impl_vector2<isq_base0<ISQ_metaArgsList>>& rhs) {
			return impl_vector2<isq_base0<ISQ_metaArgsList>>(lhs.x - rhs.x, lhs.y - rhs.y);
		}
		template<ISQ_metaArgsDefinition>
		inline void operator-=(impl_vector2<isq_base0<ISQ_metaArgsList>>& lhs, const impl_vector2<isq_base0<ISQ_metaArgsList>>& rhs) {
			lhs = (lhs - rhs);
		}

		/**DIVISION**/
		//operator/(vector2, vector2)
		template<ISQ_metaArgsComboDefinition>
		inline impl_vector2<isq_base0<ISQ_metaArgsDivision>>
			operator/(const impl_vector2<isq_base0<ISQ_metaArgsList>>& lhs,
				const impl_vector2<isq_base0<ISQ_metaArgsSecondaryList>>& rhs) {
			return impl_vector2<isq_base0<ISQ_metaArgsDivision>>(lhs.x / rhs.x, lhs.y / rhs.y);
		}
		//operator/(vector2, scalar) [dimensional]
		template<ISQ_metaArgsComboDefinition>
		inline impl_vector2<isq_base0<ISQ_metaArgsDivision>>
			operator/(const impl_vector2<isq_base0<ISQ_metaArgsList>>& lhs,
				const isq_base0<ISQ_metaArgsSecondaryList>& rhs) {
			return impl_vector2<isq_base0<ISQ_metaArgsDivision>>(lhs.x / rhs, lhs.y / rhs);
		}
		//operator/(vector2, scalar)
		template<ISQ_metaArgsDefinition>
		inline impl_vector2<isq_base0<ISQ_metaArgsList>>
			operator/(const impl_vector2<isq_base0<ISQ_metaArgsList>>& lhs, const double& rhs) {
			return impl_vector2<isq_base0<ISQ_metaArgsList>>(lhs.x / rhs, lhs.y / rhs);
		}
		//operator/(scalar, vector2)
		template<ISQ_metaArgsComboDefinition>
		inline impl_vector2<isq_base0<ISQ_metaArgsSecondaryList>>
			operator/(const isq_base0<ISQ_metaArgsList>& lhs,
				const impl_vector2<isq_base0<ISQ_metaArgsSecondaryList>>& rhs) {
			return impl_vector2<isq_base0<ISQ_metaArgsSecondaryList>>(lhs / rhs.x, lhs / rhs.y);
		}
		//operator/=(anonymous, anonymous)
		template<typename T_d1, typename T_d2>
		inline void operator/=(T_d1& lhs, const T_d2 rhs) {
			lhs = (lhs / rhs);
		}

		/**MULTIPLICATION**/
		//operator*(vector2, vector2)
		template<ISQ_metaArgsComboDefinition>
		inline impl_vector2<isq_base0<ISQ_metaArgsMultiplication>>
			operator*(const impl_vector2<isq_base0<ISQ_metaArgsList>>& lhs,
				const impl_vector2<isq_base0<ISQ_metaArgsSecondaryList>>& rhs) {
			return impl_vector2<isq_base0<ISQ_metaArgsMultiplication>>(lhs.x*rhs.x, lhs.y*rhs.y);
		}
		//operator*(vector2, scalar)
		template<ISQ_metaArgsComboDefinition>
		inline impl_vector2<isq_base0<ISQ_metaArgsMultiplication>>
			operator*(const impl_vector2<isq_base0<ISQ_metaArgsList>>& lhs,
				const isq_base0<ISQ_metaArgsSecondaryList>& rhs) {
			return impl_vector2<isq_base0<ISQ_metaArgsMultiplication>>(lhs.x*rhs, lhs.y*rhs);
		}
		//operator*(scalar, vector2)
		template<ISQ_metaArgsComboDefinition>
		inline impl_vector2<isq_base0<ISQ_metaArgsMultiplication>>
			operator*(const isq_base0<ISQ_metaArgsList>& lhs,
				const impl_vector2<isq_base0<ISQ_metaArgsSecondaryList>>& rhs) {
			return impl_vector2<isq_base0<ISQ_metaArgsMultiplication>>(lhs*rhs.x, lhs*rhs.y);
		}
		//operator*(vector2, double)
		template<ISQ_metaArgsDefinition>
		inline impl_vector2<isq_base0<ISQ_metaArgsList>>
			operator*(const impl_vector2<isq_base0<ISQ_metaArgsList>>& lhs, const double& rhs) {
			return impl_vector2<isq_base0<ISQ_metaArgsList>>(lhs.x.value*rhs, lhs.y.value*rhs);
		}
		//operator*=(anonymous, anonymous)
		template<typename T_d1, typename T_d2>
		inline void operator*=(T_d1& lhs, const T_d2& rhs) {
			lhs = (lhs * rhs);
		}

		/**COMPARISON**/
		//operator==(isq_base0, isq_base0)
		template<ISQ_metaArgsDefinition>
		bool
			operator==(const isq_internal::impl_vector2<isq_base0<ISQ_metaArgsList>>& lhs,
				const isq_internal::impl_vector2<isq_base0<ISQ_metaArgsList>>& rhs) {
			if (!(std::fabs(lhs.x.value - rhs.x.value) < std::numeric_limits<double>::epsilon())) return false;
			if (!(std::fabs(lhs.y.value - rhs.y.value) < std::numeric_limits<double>::epsilon())) return false;
			return true;
		}

		/***********/
		/**VECTOR3**/
		/***********/
		template<typename T_dim>
		class impl_vector3
		{
			impl_vector3(T_dim _x = 0, T_dim _y = 0, T_dim _z = 0) : x(_x), y(_y), z(_z) {};
			impl_vector3<T_dim> operator=(const impl_vector3<T_dim> rhs) {
				this->x = rhs.x;
				this->y = rhs.y;
				this->z = rhs.z;
				return *this;
			};

			T_dim x;
			T_dim y;
			T_dim z;
		};

		/***********/
		/**VECTORP**/
		/***********/
		template<typename T_dim>
		class impl_vectorP
		{
		public:
			impl_vectorP(T_dim _m, si::angle _th) : m(_m), th(_th) {};
			T_dim m;
			si::angle th;

			operator impl_vector2<T_dim>() const {
				T_dim x = m * std::cos(th);
				T_dim y = m * std::sin(th);
				return impl_vector2<T_dim>(x, y);
			}
		};
	}

	namespace vec
	{
		typedef isq_internal::impl_vector2<isq_base0<ISQ_baseMetaArgs_VELO>> velocity;
		typedef isq_internal::impl_vector2<isq_base0<ISQ_baseMetaArgs_ACCL>> acceleration;
		typedef isq_internal::impl_vector2<isq_base0<ISQ_baseMetaArgs_LENG>> position;
		typedef isq_internal::impl_vector2<isq_base0<ISQ_baseMetaArgs_AREA>> field;
		typedef isq_internal::impl_vector2<isq_base0<ISQ_baseMetaArgs_LENG>> displacement;
		typedef isq_internal::impl_vector2<isq_base0<ISQ_baseMetaArgs_FORC>> force;
		typedef isq_internal::impl_vector2<isq_base0<ISQ_baseMetaArgs_MOMT>> momentum;
		typedef isq_internal::impl_vector2<isq_base0<ISQ_baseMetaArgs_JOLT>> jolt;
		typedef isq_internal::impl_vector2<isq_base0<ISQ_baseMetaArgs_DLES>> dimensionless;
	}

	namespace vec3
	{
		typedef isq_internal::impl_vector3<isq_base0<ISQ_baseMetaArgs_VELO>> velocity;
		typedef isq_internal::impl_vector3<isq_base0<ISQ_baseMetaArgs_ACCL>> acceleration;
		typedef isq_internal::impl_vector3<isq_base0<ISQ_baseMetaArgs_LENG>> position;
		typedef isq_internal::impl_vector3<isq_base0<ISQ_baseMetaArgs_AREA>> field;
		typedef isq_internal::impl_vector3<isq_base0<ISQ_baseMetaArgs_LENG>> displacement;
		typedef isq_internal::impl_vector3<isq_base0<ISQ_baseMetaArgs_FORC>> force;
		typedef isq_internal::impl_vector3<isq_base0<ISQ_baseMetaArgs_MOMT>> momentum;
		typedef isq_internal::impl_vector3<isq_base0<ISQ_baseMetaArgs_JOLT>> jolt;
		typedef isq_internal::impl_vector3<isq_base0<ISQ_baseMetaArgs_DLES>> dimensionless;
	}

	namespace pvec
	{
		typedef isq_internal::impl_vectorP<isq_base0<ISQ_baseMetaArgs_VELO>> velocity;
		typedef isq_internal::impl_vectorP<isq_base0<ISQ_baseMetaArgs_ACCL>> acceleration;
		typedef isq_internal::impl_vectorP<isq_base0<ISQ_baseMetaArgs_LENG>> position;
		typedef isq_internal::impl_vectorP<isq_base0<ISQ_baseMetaArgs_AREA>> field;
		typedef isq_internal::impl_vectorP<isq_base0<ISQ_baseMetaArgs_LENG>> displacement;
		typedef isq_internal::impl_vectorP<isq_base0<ISQ_baseMetaArgs_FORC>> force;
		typedef isq_internal::impl_vectorP<isq_base0<ISQ_baseMetaArgs_MOMT>> momentum;
		typedef isq_internal::impl_vectorP<isq_base0<ISQ_baseMetaArgs_JOLT>> jolt;
		typedef isq_internal::impl_vectorP<isq_base0<ISQ_baseMetaArgs_DLES>> dimensionless;
	}

	/*namespace nodim
	{
	typedef isq_base0<ISQ_baseMetaArgs_DLES> reynolds;
	}*/

#undef ISQ_baseMetaArgs_LENG
#undef ISQ_baseMetaArgs_MASS
#undef ISQ_baseMetaArgs_TIME
#undef ISQ_baseMetaArgs_CURR
#undef ISQ_baseMetaArgs_TEMP
#undef ISQ_baseMetaArgs_AMTS
#undef ISQ_baseMetaArgs_INTS
#undef ISQ_baseMetaArgs_AREA
#undef ISQ_baseMetaArgs_VOLM
#undef ISQ_baseMetaArgs_VELO
#undef ISQ_baseMetaArgs_ACCL
#undef ISQ_baseMetaArgs_JOLT
#undef ISQ_baseMetaArgs_ANGV
#undef ISQ_baseMetaArgs_MOMT
#undef ISQ_baseMetaArgs_ANGM
#undef ISQ_baseMetaArgs_TORQ
#undef ISQ_baseMetaArgs_ARDN
#undef ISQ_baseMetaArgs_DENS
#undef ISQ_baseMetaArgs_SVOL
#undef ISQ_baseMetaArgs_HCAP
#undef ISQ_baseMetaArgs_MHCP
#undef ISQ_baseMetaArgs_SHCP
#undef ISQ_baseMetaArgs_SENG
#undef ISQ_baseMetaArgs_ENDN
#undef ISQ_baseMetaArgs_STNS
#undef ISQ_baseMetaArgs_HFLX
#undef ISQ_baseMetaArgs_TCON
#undef ISQ_baseMetaArgs_KVIS
#undef ISQ_baseMetaArgs_DVIS
#undef ISQ_baseMetaArgs_HRTZ
#undef ISQ_baseMetaArgs_FORC
#undef ISQ_baseMetaArgs_PRES
#undef ISQ_baseMetaArgs_ENRG
#undef ISQ_baseMetaArgs_POWR
#undef ISQ_baseMetaArgs_CHRG
#undef ISQ_baseMetaArgs_VOLT
#undef ISQ_baseMetaArgs_ECAP
#undef ISQ_baseMetaArgs_ERES
#undef ISQ_baseMetaArgs_ECON
#undef ISQ_baseMetaArgs_MFLX
#undef ISQ_baseMetaArgs_INDC
#undef ISQ_baseMetaArgs_LFLX
#undef ISQ_baseMetaArgs_ILLM
#undef ISQ_baseMetaArgs_RDAC
#undef ISQ_baseMetaArgs_RDAD
#undef ISQ_baseMetaArgs_RDED
#undef ISQ_baseMetaArgs_CATA
#undef ISQ_baseMetaArgs_GENR


}// namespace si
#endif // ISQPP_H