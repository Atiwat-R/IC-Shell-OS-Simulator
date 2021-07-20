<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<html>
<head>
    <title>Login Webapp</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css"
          integrity="sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh" crossorigin="anonymous">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js"
            integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM"
            crossorigin="anonymous"></script>
    <link rel="stylesheet"
          href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css"
          integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm"
          crossorigin="anonymous">
</head>
<body>
<div class="container mt-4">
    <nav class="navbar navbar-light bg-light">
        <div class="container-fluid">
            <a class="navbar-brand">SSC Login Webapp</a>
            <a class="btn btn-gray btn-sm" type="button" href="/logout">
                Logout</a>
        </div>
    </nav>

    <c:if test="${not empty message}">
        <c:choose>
            <c:when test="${empty var1}">
                <div class="alert alert-success" role="alert">
                        ${message}
                </div>
            </c:when>
            <c:otherwise>
                <div class="alert alert-danger" role="alert">
                        ${message}
                </div>
            </c:otherwise>
        </c:choose>

    </c:if>


    <div class="row justify-content-md-center">
        <div class="col-sm-12 col-md-3">

            <h3>Create New User</h3>
            <p>${error}</p>
            <form action="/user/create" method="post" autocomplete="off">
                <%--Username:--%>
                <br/>
                <input type="text" class="form-control" name="username" placeholder="Username" aria-label="Username"
                       aria-describedby="username" value="${username}"/>
                <br/>
                <%--Display Name:--%>
                <br/>
                <input type="text" class="form-control" name="displayName" placeholder="Display Name"
                       aria-label="displayName" aria-describedby="displayName" value="${displayName}"/>
                <br/>
                <%--Password:--%>
                <br/>
                <input type="password" class="form-control" name="password" placeholder="Password" aria-label="Password"
                       aria-describedby="password" value="${password}">
                <br>
                <%--Confirm Password:--%>
                <br/>
                <input type="password" class="form-control" name="cpassword" placeholder="Confirm Password"
                       aria-label="Password" aria-describedby="password" value="${cpassword}">
                <br><br>
                <button class="btn btn-success" type="submit" value="">Create User</button>
            </form>

        </div>
    </div>


</div>

<script src="https://code.jquery.com/jquery-3.2.1.slim.min.js"
        integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN"
        crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js"
        integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q"
        crossorigin="anonymous"></script>
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js"
        integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl"
        crossorigin="anonymous"></script>

</body>
</html>
<%
    request.removeAttribute("hasError");
    request.removeAttribute("message");
%>
