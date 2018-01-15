#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SDLFramework/Vector.h"
#include "../SDLFramework/Vector.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(VectorTests)
	{
	public:

		TEST_METHOD(BasicComponentsTest)
		{
			Vec vec{ 1.f, 2.f, 3.f };

			Assert::AreEqual(vec[0], 1.f);
			Assert::AreEqual(vec[1], 2.f);
			Assert::AreEqual(vec[2], 3.f);
		}

		TEST_METHOD(BasicSpecializationComponentsTest)
		{
			Vec3 vec{ 1.f, 2.f, 3.f };

			Assert::AreEqual(vec.x(), 1.f);
			Assert::AreEqual(vec.y(), 2.f);
			Assert::AreEqual(vec.z(), 3.f);
		}

		TEST_METHOD(MultiplyByScalar)
		{
			Vec3 vec{ 1.f, 2.f, 3.f };
			vec *= 2.f;

			Assert::AreEqual(vec.x(), 1.f * 2.f);
			Assert::AreEqual(vec.y(), 2.f * 2.f);
			Assert::AreEqual(vec.z(), 3.f * 2.f);
		}

		TEST_METHOD(NormalizeLengthIsOne)
		{
			Vec3 vec{ 1.f, 2.f, 3.f };
			vec = vec.normalize();

			float len = vec.length();

			Assert::AreEqual(vec.length(), 1.f, FLT_EPSILON);
		}

		TEST_METHOD(NormalizeComponents)
		{
			Vec3 vec{ 1.f, 2.f, 3.f };
			float expected = sqrt(1.f * 1.f + 2.f * 2.f + 3.f * 3.f);

			Assert::AreEqual(expected, vec.length(), FLT_EPSILON);
		}

		TEST_METHOD(OperatorAdd)
		{
			Vec3 vec{ 1.f, 2.f, 3.f };
			vec += Vec3{ 5.f, 6.f, 7.f };

			Assert::AreEqual(vec.x(), 1.f + 5.f);
			Assert::AreEqual(vec.y(), 2.f + 6.f);
			Assert::AreEqual(vec.z(), 3.f + 7.f);
		}

	};
}