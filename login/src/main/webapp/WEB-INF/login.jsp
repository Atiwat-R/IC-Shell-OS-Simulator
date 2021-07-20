<html>
<head>
    <title>Login Webapp</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css"
          integrity="sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh" crossorigin="anonymous">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js"
            integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM"
            crossorigin="anonymous"></script>
</head>
<body>
<div class="container mt-4">
    <div class="row justify-content-md-center">
        <div class="col-sm-12 col-md-3">
            <h2>Login</h2>
            <p>${error}</p>
            <form action="/login" method="post">
                Username:<br/>
                <input type="text" class="form-control" name="username" placeholder="Username" aria-label="Username" aria-describedby="username"/>
                <br/>
                Password:<br/>
                <input type="password" class="form-control" name="password"  placeholder="Password" aria-label="Password" aria-describedby="password">
                <br><br>
                <button class="btn btn-primary" type="submit" value="">Submit</button>
            </form>
        </div>
    </div>

</div>
</body>
</html>
