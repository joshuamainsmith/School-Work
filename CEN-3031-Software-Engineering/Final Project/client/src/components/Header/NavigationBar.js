import React, { useContext, useState } from 'react';
import { withRouter } from 'react-router-dom';
import AuthService from '../../Services/AuthService'
import { AuthContext } from '../../Context/AuthContext'
import Gator from './logo.png';
import './NavigationBar.css';

const NavigationBar = (props) => {
	const {isAuthenticated, user, setIsAuthenticated, setUser} = useContext(AuthContext);

	const onClickLogoutHandler = () => {
		AuthService.logout().then(data => {
			
			if(data.success) {
				setUser(data.user);
				setIsAuthenticated(false);
				
				props.history.push('/user/login');
			}
		})
	}

	const unauthenticatedNav = () => {
			return (
				<>
				<li className="nav-item active">
					<a className="nav-link" href="/user/login">
						Login
					</a>
				</li>
				<li className="nav-item active">
					<a className="nav-link" href="/user/signup">
						Register
					</a>
				</li>
				</>
			)
	}

	const authenticatedAdminNav = () => {
		return (
			<>
				<li className="nav-item">
					<a className="nav-link" href="/careers">
						Careers
					</a>
				</li>
				<li className="nav-item">
					<a className="nav-link" href="/clusters">
						Clusters
					</a>
				</li>
				<li className="nav-item">
					<a className="nav-link" href="/celebs">
						Celebrities
					</a>
				</li>

				{
					user.role === "admin" ?
					<li className="nav-item dropdown">
						<a
							className="nav-link dropdown-toggle"
							href="/"
							id="navbarDropdown"
							role="button"
							data-toggle="dropdown"
							aria-haspopup="true"
							aria-expanded="false"
						>
							Admin
						</a>

						<div className="dropdown-menu" aria-labelledby="navbarDropdown">
							<a className="dropdown-item" href="/career">
								Create Career
							</a>
							<a className="dropdown-item" href="/cluster/create">
								Create Cluster
							</a>
							<a className="dropdown-item" href="/careers">
								Careers
							</a>
							<a className="dropdown-item" href="/clusters">
								Clusters
							</a>
							<a className="dropdown-item" href="/users">
								Users
							</a>
						</div>
					</li> : null
				}
				<li>
					<button type="button"
								className="btn btn-link nav-item nav-link"
								onClick={onClickLogoutHandler}>Logout</button>
				</li>
			</>
		)
	}

	return (
		<>
			<nav className="navbar navbar-expand-xl navbar-light bg-light navbar-fixed-top">
				<a className="navbar-brand header-sty" href="/">
					Career Finder
				</a>
				<button
					className="navbar-toggler"
					type="button"
					data-toggle="collapse"
					data-target="#navbarSupportedContent"
					aria-controls="navbarSupportedContent"
					aria-expanded="false"
					aria-label="Toggle navigation"
				>
					<span className="navbar-toggler-icon" />
				</button>

				<div className="collapse navbar-collapse" id="navbarSupportedContent">
					<ul className="navbar-nav mr-auto">
						{ isAuthenticated ? authenticatedAdminNav() : unauthenticatedNav() }
					</ul>
					{
						isAuthenticated ?
							<form className="form-inline my-2 my-lg-0" action="/careers">
								<input
									className="form-control mr-sm-4"
									type="search"
									placeholder="Search Careers"
									aria-label="Search"
									name="keyword"
								/>
								<button className="btn btn-outline-success my-2 my-sm-0" type="submit">
									Search
								</button>
							</form> : null
					}
				</div>
			</nav>
		</>
	);
};

export default withRouter (NavigationBar);
