#include "../include/endpoints.hpp"
#include <thread>

int main() {
	Database::GetInstance();
	CppHttp::Net::Router router;
	CppHttp::Net::TcpListener server;
	server.CreateSocket();

	auto onReceive = [&](CppHttp::Net::Request req) {
		router.Handle(req);
	};

	server.SetOnReceive(onReceive);

	router.AddRoute("POST", "/classroom/create", CreateClassroom);
	router.AddRoute("POST", "/classroom/{id}/add", AddUserToClassroom);
	router.AddRoute("GET", "/classroom/user/get", GetUserClassrooms);
	router.AddRoute("GET", "/classroom/{id}/get", GetClassroom);
	router.AddRoute("GET", "/classroom/{id}/member/get/all", GetClassroomMembers);
	router.AddRoute("DELETE", "/classroom/{classroom_id}/member/{member_id}/remove", RemoveUserFromClassroom);

	server.Listen("0.0.0.0", 8002, std::thread::hardware_concurrency());

	Database::GetInstance()->Close();
}