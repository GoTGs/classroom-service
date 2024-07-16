#include "../include/endpoints.hpp"
#include <thread>

int main() {
	CppHttp::Net::Router router;
	CppHttp::Net::TcpListener server;
	server.CreateSocket();

	int requestCount = 0;

	auto onReceive = [&](CppHttp::Net::Request req) {
		router.Handle(req);
	};

	server.SetOnReceive(onReceive);

	router.AddRoute("POST", "/classroom/create", CreateClassroom);
	router.AddRoute("GET", "/classroom/user/get", GetUserClassrooms);
	router.AddRoute("GET", "/classroom/{id}/get", GetClassroom);

	server.Listen("0.0.0.0", 8002, std::thread::hardware_concurrency());

	Database::GetInstance()->Close();
}