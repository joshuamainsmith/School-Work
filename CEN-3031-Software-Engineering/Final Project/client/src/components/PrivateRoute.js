// This is used to determine if a user is authenticated and
// if they are allowed to visit the page they navigated to.

// If they are: they proceed to the page
// If not: they are redirected to the login page.
import React, {useContext} from 'react'
import { Redirect, Route } from 'react-router-dom'
import { AuthContext } from '../Context/AuthContext'

const PrivateRoute = ({ component: Component, ...rest }) => {
  const {isAuthenticated} = useContext(AuthContext);


  return (
    <Route
      {...rest}
      render={props =>
        isAuthenticated ? (
          <Component {...props} />
        ) : (
          <Redirect to={{ pathname: '/user/login', state: { from: props.location } }} />
        )
      }
    />
  )
}

export default PrivateRoute
