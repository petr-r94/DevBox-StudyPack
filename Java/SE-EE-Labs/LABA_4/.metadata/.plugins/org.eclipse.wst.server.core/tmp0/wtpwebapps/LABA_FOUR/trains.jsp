<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ page import="java.util.*, java.text.*"%>
<%@ page contentType="text/html; charset=windows-1251"%>
<html>
<head>
<title>DEPO EDIT WEB APPLICATION</title>
<link rel="stylesheet" type="text/css" href="trains.css" />
<link rel="stylesheet" type="text/css" href="LoginForm.css" />
</head>

<body>
	<div id="header">
		<h1 class="mainheader">DEPO EDIT WEB APPLICATION</h1>
	</div>
	<h2 align="center" id="welcome">Welcome ${curuser} !</h2>
	<br />;
	<h2 align="center">SCHEDULE OF TRAINS</h2>
	<table class="table">
		<tr>
			<th>Locomotiv-Name</th>
			<th>Sostav-Number</th>
			<th>Locomotiv-Type</th>
			<th>CountOf-Vagon</th>
		</tr>


		<c:forEach var="column1" items="${loconame}" varStatus="status">
			<tr>
				<td>${column1}</td>
				<td>${sostavnum[status.index]}</td>
				<td>${locotype[status.index]}</td>
				<td>${countvagons[status.index]}</td>
			</tr>
		</c:forEach>
	</table>
	<div id="login">
	<form>
		<input class="button" type="button" value="Refresh Database" onClick="window.location.reload()">
	</form>
	</div>
	
	<div id="login">
	<form name="AddForm" method="post" action="addServlet">
		Locomotiv-Name: <input type="text" name="Locomotiv-Name"/> <br/>
		Sostav-Number: <input type="password" name="Sostav-Number"/> <br/>
		Locomotiv-Type: <input type="password" name="Locomotiv-Type"/> <br/>
		CountOf-Vagon: <input type="password" name="CountOf-Vagon"/> <br/>
		<input class="button" type="submit" value="Add new Sostav" />
	</form>
	</div>
	
	<div id="login">
	<form name="DelForm" method="post" action="delServlet">
		Sostav-Number: <input type="password" name="Sostav-Number"/> <br/>
		<input class="button" type="submit" value="Delete Sostav" />
	</form>
	</div>
</body>
</html>