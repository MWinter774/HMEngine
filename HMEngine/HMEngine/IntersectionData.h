#pragma once

namespace HMEngine
{
	namespace Core
	{
		namespace Physics
		{
			class IntersectionData
			{
			public:
				IntersectionData(bool isIntersect, float distance);
				~IntersectionData();

				inline bool IsIntersect() const { return this->_isIntersect; }
				inline float GetDistance() const { return this->_distance; }

			private:
				bool _isIntersect;
				float _distance;
			};
		}
	}
}