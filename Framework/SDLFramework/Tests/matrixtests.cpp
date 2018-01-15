#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SDLFramework/Matrix.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(MatrixTests)
	{
	public:

		TEST_METHOD(TestMutiplication)
		{
			Matrix a
			{
				{ 1, 4, 6, 10 },
				{ 2, 7, 5, 3 }
			};

			Matrix b
			{
				{ 1, 4, 6 },
				{ 2, 7, 5 },
				{ 9, 0, 11 },
				{ 3, 1, 0 }
			};

			auto c = a * b;

			Matrix expected{
				{ 93, 42, 92 },
				{ 70, 60, 102 }
			};

			Assert::IsTrue(expected == c);
		}

		TEST_METHOD(TestMutiplication2)
		{
			Matrix a
			{
				{ -3, -2, -1 },
				{ 2, 3, 0 },
				{ 1, 4, 5 },
				{ 6, 7, 8 }
			};

			Matrix b
			{
				{ 9, -3, -1 },
				{ -4, 10, 11 },
				{ -2, 0, 2 }
			};

			auto c = a * b;

			Matrix expected{
				{ -17, -11, -21 },
				{ 6, 24, 31 },
				{ -17, 37, 53 },
				{ 10, 52, 87 }
			};

			Assert::IsTrue(expected == c);
		}

		TEST_METHOD(InitFromVector)
		{
			Matrix a
			{
				Vec{ -3, -2, -1 },
				Vec{ 2, 3, 0 },
				Vec{ 1, 4, 5 },
				Vec{ 6, 7, 8 }
			};


			Assert::AreEqual(a.columns(), size_t{ 4 });
			Assert::AreEqual(a.rows(), size_t{ 3 });
		}

		TEST_METHOD(InitFromVectorOrder)
		{
			Matrix a
			{
				Vec{ -3, -2, -1 },
				Vec{ 2, 3, 0 },
				Vec{ 1, 4, 5 },
				Vec{ 6, 7, 8 }
			};

			Assert::IsTrue(a[0] == Vec{ -3.f, -2.f, -1.f });
			Assert::IsTrue(a(1, 0) == -2.f);
		}
	};
}