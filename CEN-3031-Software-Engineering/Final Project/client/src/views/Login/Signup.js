import React, {useState, useRef, useEffect} from 'react';
import AuthService from '../../Services/AuthService'
import Message from '../../components/Message/Message'
//import { AuthContext } from '../../Context/AuthContext'
import './UserLogin.css';

const Signup = (props) => {
	const [user, setUser] = useState({username: "", password: ""});
	const [message, setMessage] = useState(null);
	let timerID = useRef(null);

	useEffect(() => {
		return () => {
			clearTimeout(timerID);
		}
	}, [])

	const onChange = e => {
		setUser({...user, [e.target.name] : e.target.value});
	}

	const resetForm = () => {
		setUser({username: "", password: "", role: ""});
	}

	const onSubmit = e => {
		e.preventDefault();
		AuthService.register(user).then(data => {
			const { message } = data;
			setMessage(message);
			resetForm();
			if(!message.msgError) {
				timerID = setTimeout(() => {
					props.history.push('/user/login');
				}, 2000)
			}
		});
	}

	return (
		<>
		<div className="container">
			<div className="row">
				<div className="col-sm-9 col-md-7 col-lg-5 mx-auto">
					<div className="card card-signin my-5">
						<div className="card-body">
							<h5 className="card-title text-center">Please Register</h5>
							<form className="form-signin" onSubmit={onSubmit}>
								<div className="form-label-group">
									<input type="text"
												 id="email"
												 name="email"
												 onChange={onChange}
												 className="form-control"
												 placeholder="Email" required autofocus></input>
									<label htmlFor="email">Enter Email</label>
								</div>

								<div className="form-label-group">
									<input type="text"
												 id="username"
												 name="username"
											   onChange={onChange}
											   className="form-control"
											   placeholder="Username" required></input>
									<label htmlFor="username">Enter Username</label>
								</div>

								<div className="form-label-group">
									<input type="password"
												 id="password"
												 name="password"
												 onChange={onChange}
												 className="form-control"
												 placeholder="Password"
												 minlength="6" required></input>
									<label htmlFor="password">Enter Password</label>
								</div>
								<button className="btn btn-lg btn-primary btn-block text-uppercase"
												type="submit">Register</button>
							</form>
							{message ? <Message message={message}/> : null}
						</div>
					</div>
				</div>
			</div>
		</div>
		</>
	);
};

export default Signup;
