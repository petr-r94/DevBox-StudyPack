<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ page import="java.util.*, java.text.*"%>
<%@ page contentType="text/html; charset=windows-1251"%>
<html>
<head>
<title>Login Form</title>
<link rel="stylesheet" type="text/css" href="LoginForm.css" />
</head>
<body>
<div id="header">
<h1 class="mainheader">DEPO AUTHENIFICATION SYSTEM</h1>
</div>
	<div id="login">
	<form name="loginForm" method="post" action="loginServlet">
		Username: <input type="text" name="username"/> <br/>
		Password: <input type="password" name="password"/> <br/>
		<input class="button" type="submit" value="Login" />
	</form>
	
	<form name="RegForm" method="post" action="regServlet">
	    New Username: <input type="text" name="newusername"/> <br/>
		New Password: <input type="password" name="newpassword"/> <br/>
	<input class="but" type="submit" value="Register" />
	</form>
	</div>
<h1 class="invalidheader">Invalid Registration Data for ' ${curuser} '!</h1>
</body>
</html>