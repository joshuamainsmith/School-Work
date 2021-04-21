import React, {useState, useContext} from 'react';
import AuthService from '../../Services/AuthService'
//import Message from '../../components/Message/Message'
import { AuthContext } from '../../Context/AuthContext'
import './UserLogin.css';

const Login = (props) => {
	const [user, setUser] = useState({username: "", password: ""});
	const [message, setMessage] = useState(null);
	const authContext = useContext(AuthContext)

	const onChange = e => {
		e.preventDefault();
		setUser({...user, [e.target.name] : e.target.value});
	}

	const onSubmit = e => {
		e.preventDefault();
		AuthService.login(user).then(data => {
			const { isAuthenticated, user, message } = data;

			if(isAuthenticated) {
				authContext.setUser(user);
				authContext.setIsAuthenticated(isAuthenticated);
				props.history.push('/careers')
			} else {
				console.log(message);
				setMessage(message);
			}
		});
	}

	return (
		<div className="container">
			<div className="row">
				<div className="col-sm-9 col-md-7 col-lg-5 mx-auto">
					<div className="card card-signin my-5">
						<div className="card-body">
							<h5 className="card-title text-center">Sign In</h5>
							<form className="form-signin" onSubmit={onSubmit}>
								<div className="form-label-group">
									<input type="text"
												 id="username"
												 name="username"
											   onChange={onChange}
											   className="form-control"
											   placeholder="Username" required autoFocus></input>
									<label htmlFor="username">Username</label>
								</div>

								<div className="form-label-group">
									<input type="password"
												 id="password"
												 name="password"
												 onChange={onChange}
												 className="form-control"
												 placeholder="Password" required></input>
									<label htmlFor="password">Password</label>
								</div>
								<button className="btn btn-lg btn-primary btn-block text-uppercase"
												type="submit">Sign in</button>
								<hr className="my-4"/>
								<a className="btn btn-sm col-md-12" href="/user/signup">Register</a>
							</form>
						</div>
					</div>
				</div>
			</div>
		</div>
	);
};

export default Login;
