# hiredis


create somredis library by hiredis
code coverage
{
	cmake ..
	make
	./test
	gcov ./CMakeFiles/somredis.dir/src/SomRedis.cpp.gcno
	vim SomRedis.cpp.gcov
}
