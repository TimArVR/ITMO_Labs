#include "pch.h"
#include <string>
#include "../MyDynamicArray/MyDynamicArray.h"

TEST(Array, Can_Create_Default_Object_Size) 
{
	Array <int> a;
	ASSERT_EQ (a.Size(), 0);
}

TEST(Array, Can_Create_Default_Object_Capacity)
{
	Array <int> a;
	ASSERT_EQ(a.Capacity(), 16);
}

TEST(Array, Can_Create_Object_with_Capacity)
{
	int capacity = 100;
	Array <int> a(capacity);
	ASSERT_EQ(a.Capacity(), capacity);
}

TEST(Array, Can_Create_Object_withCapacity_eqZeroSize)
{
	int capacity = 100;
	Array <int> a(capacity);
	ASSERT_EQ(a.Size(), 0);
}

TEST(Array, CanCopyObject_SizeCaptheSame)
{
	Array <int> a;
	Array <int> b(a);
	ASSERT_EQ(a.Size(), b.Size());
	ASSERT_EQ(a.Capacity(), b.Capacity());
}

TEST(Array, CopyConstr_members_prim)
{
	Array <int> a(10);
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(i);
	}

	Array <int> b(a);

	for (size_t i = 0; i < 10; i++)
	{
		ASSERT_EQ(a[i], b[i]);
	}
}

TEST(Array, CopyConstr_members_string)
{
	std::string TestString = "100000000000000000000000000000000000000000000000";
	Array <std::string> a;
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(TestString+std::to_string(i));
	}

	Array <std::string> b(a);

	for (size_t i = 0; i < 10; i++)
	{
		ASSERT_EQ(a[i], b[i]);
	}
}



TEST(Array, MoveConstr_members_prim_capacity)
{
	Array <int> a;
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(i);
	}
	int TestCap = a.Capacity();
	Array <int> b(std::move(a));

	ASSERT_EQ(TestCap, b.Capacity());

}

TEST(Array, MoveConstr_members_prim_size)
{
	Array <int> a;
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(i);
	}
	int TestSize = a.Size();
	Array <int> b(std::move(a));

	ASSERT_EQ(TestSize, b.Size());

}

TEST(Array, CopyConstr_members_string_capacity)
{
	std::string TestString = "100000000000000000000000000000000000000000000000";
	Array <std::string> a;
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(TestString + std::to_string(i));
	}
	int TestCap = a.Capacity();
	Array <std::string> b(a);

	ASSERT_EQ(TestCap, b.Capacity());
}

TEST(Array, CopyConstr_members_string_size)
{
	std::string TestString = "100000000000000000000000000000000000000000000000";
	Array <std::string> a;
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(TestString + std::to_string(i));
	}
	int TestSize = a.Size();
	Array <std::string> b(a);

	ASSERT_EQ(TestSize, b.Size());
}


TEST(Array, MoveConstr_members_string_capacity)
{
	std::string TestString = "100000000000000000000000000000000000000000000000";
	Array <std::string> a;
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(TestString+std::to_string(i));
	}
	int TestCap = a.Capacity();
	Array <std::string> b(std::move(a));

	ASSERT_EQ(TestCap, b.Capacity());
}

TEST(Array, MoveConstr_members_string_size)
{
	std::string TestString = "100000000000000000000000000000000000000000000000";
	Array <std::string> a;
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(TestString + std::to_string(i));
	}
	int TestSize = a.Size();
	Array <std::string> b(std::move(a));

	ASSERT_EQ(TestSize, b.Size());
}

TEST(Array, MoveConstr_members_prim)
{
	Array <int> a(10);
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(i);
	}

	Array <int> b(std::move(a));

	for (size_t i = 0; i < 10; i++)
	{
		ASSERT_EQ(i, b[i]);
	}
}

TEST(Array, MoveConstr_members_string)
{
	std::string TestString = "100000000000000000000000000000000000000000000000";
	Array <std::string> a;
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(TestString + std::to_string(i));
	}

	Array <std::string> b(std::move(a));

	for (int i = 0; i < 10; i++)
	{
		ASSERT_EQ(b[i], TestString + std::to_string(i));
	}
}

TEST(Array, Can_Insert_without_Index_Primitive)
{
	Array <int> a;
	a.Insert(10);
	a.Insert(20);

	ASSERT_EQ(a.Size(), 2);
	ASSERT_EQ(a[0], 10);
}

TEST(Array, Can_Insert_with_Index_Primitive)
{
	Array <int> a;
	a.Insert(10);
	a.Insert(20);
	a.Insert(30);
	a.Insert(2,100);

	ASSERT_EQ(a[2], 100);
}

TEST(Array, Can_Insert_without_Index_String)
{
	Array <std::string> a;
	a.Insert("100000000000000000000000000000000000000000000000000000000000000");
	a.Insert("200000000000000000000000000000000000000000000000000000000000000");

	ASSERT_EQ(a.Size(), 2);
	ASSERT_EQ(a[0], "100000000000000000000000000000000000000000000000000000000000000");
	ASSERT_EQ(a[1], "200000000000000000000000000000000000000000000000000000000000000");
}

TEST(Array, Can_Insert_with_Index_String)
{
	Array <std::string> a;
	const std::string kTestString = "900000000000000000000000000000000000000000000000000000000000000";
	a.Insert("100000000000000000000000000000000000000000000000000000000000000");
	a.Insert("200000000000000000000000000000000000000000000000000000000000000");
	a.Insert("300000000000000000000000000000000000000000000000000000000000000");
	a.Insert(1, kTestString);

	ASSERT_EQ(a[1], kTestString);
}

TEST(Array, Can_Insert_with_Index_Primitive_with_2Capacity)
{
	int capacity = 3;
	Array <int> a(capacity);
		
	a.Insert(10);
	a.Insert(20);
	a.Insert(30);
	a.Insert(1, 90);

	ASSERT_EQ(a.Capacity(), capacity * 2);
}

TEST(Array, Can_Insert_with_Index_String_with_2Capacity)
{
	int capacity = 3;
	Array <std::string> a(capacity);

	const std::string kTestString = "900000000000000000000000000000000000000000000000000000000000000";
	a.Insert("100000000000000000000000000000000000000000000000000000000000000");
	a.Insert("200000000000000000000000000000000000000000000000000000000000000");
	a.Insert("300000000000000000000000000000000000000000000000000000000000000");
	a.Insert(1, kTestString);

	ASSERT_EQ(a.Capacity(), capacity*2);
}

TEST(Array, CopyOperator_members_prim)
{
	Array <int> a(10);
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(i);
	}

	Array <int> b = a;

	for (size_t i = 0; i < 10; i++)
	{
		ASSERT_EQ(a[i], b[i]);
	}
}

TEST(Array, CopyOperator_members_string)
{
	std::string TestString = "100000000000000000000000000000000000000000000000";
	Array <std::string> a;
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(TestString + std::to_string(i));
	}

	Array <std::string> b = a;

	for (size_t i = 0; i < 10; i++)
	{
		ASSERT_EQ(a[i], b[i]);
	}
}

TEST(Array, CopyOperator_members_string_capacity)
{
	std::string TestString = "100000000000000000000000000000000000000000000000";
	Array <std::string> a;
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(TestString + std::to_string(i));
	}
	int TestCap = a.Capacity();
	Array <std::string> b = a;

	ASSERT_EQ(TestCap, b.Capacity());
}

TEST(Array, CopyOperator_members_string_size)
{
	std::string TestString = "100000000000000000000000000000000000000000000000";
	Array <std::string> a;
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(TestString + std::to_string(i));
	}
	int TestSize = a.Size();
	Array <std::string> b = a;

	ASSERT_EQ(TestSize, b.Size());
}

TEST(Array, MoveOperator_members_string_capacity)
{
	std::string TestString = "100000000000000000000000000000000000000000000000";
	Array <std::string> a;
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(TestString + std::to_string(i));
	}
	int TestCap = a.Capacity();
	Array <std::string> b = std::move(a);

	ASSERT_EQ(TestCap, b.Capacity());
}

TEST(Array, MoveOperator_members_string_size)
{
	std::string TestString = "100000000000000000000000000000000000000000000000";
	Array <std::string> a;
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(TestString + std::to_string(i));
	}
	int TestSize = a.Size();
	Array <std::string> b = std::move(a);

	ASSERT_EQ(TestSize, b.Size());
}

TEST(Array, MoveOperator_members_prim)
{
	Array <int> a(10);
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(i);
	}

	Array <int> b = std::move(a);

	for (size_t i = 0; i < 10; i++)
	{
		ASSERT_EQ(i, b[i]);
	}
}

TEST(Array, MoveOperator_members_string)
{
	std::string TestString = "100000000000000000000000000000000000000000000000";
	Array <std::string> a;
	for (size_t i = 0; i < 10; i++)
	{
		a.Insert(TestString + std::to_string(i));
	}

	Array <std::string> b = std::move(a);

	for (int i = 0; i < 10; i++)
	{
		ASSERT_EQ(b[i], TestString + std::to_string(i));
	}
}

TEST(Array, Remove_members_prim)
{
	int TestIndex = 3;
	int TestCapacity = 10;
	Array <int> a(TestCapacity);
	for (int i = 0; i < TestCapacity; i++)
	{
		a.Insert(i);
	}

	a.Remove(TestIndex);
	
	ASSERT_EQ(a.Size(), TestCapacity-1);;	
}

TEST(Array, Remove_members_string)
{
	std::string TestStr = "10000000000000000000000000000000000000000000000000000000000000000";
	int TestCapacity = 10;
	Array <std::string> a(TestCapacity);
	for (int i = 0; i < TestCapacity; i++)
	{
		a.Insert(TestStr+std::to_string(i));
	}
	a.Remove(3);

	ASSERT_EQ(a.Size(), TestCapacity - 1);;
}

TEST(Array, Can_Get_Iterator_string)
{
	std::string TestStr = "10000000000000000000000000000000000000000000000000000000000000000";
	int TestCapacity = 10;
	Array <std::string> a(TestCapacity);
	for (int i = 0; i < TestCapacity; ++i)
	{
		a.Insert(TestStr + std::to_string(i));
	}
	
	int i = 0;

	for (auto it = a.iterator(); it.HasNext(); it.Next(), ++i)
	{		
		ASSERT_EQ(it.Get(), TestStr + std::to_string(i));
	}
}

TEST(Array, Can_Get_Reverse_Iterator_string)
{
	std::string TestStr = "10000000000000000000000000000000000000000000000000000000000000000";
	int TestCapacity = 10;
	int i = TestCapacity - 1;

	Array <std::string> a(TestCapacity);
	for (int i = 0; i < TestCapacity; ++i)
	{
		a.Insert(TestStr + std::to_string(i));
	}
	
	for (auto it = a.ReverseIterator(); it.HasNext(); it.Next(), --i)
	{
		ASSERT_EQ(it.Get(), TestStr + std::to_string(i));
	}
}

TEST(Array, Can_Insert_with_Index_FIX)
{
	Array <int> a;
	a.Insert(10); //0
	a.Insert(1, 333);

	ASSERT_EQ(a[1], 333);

}