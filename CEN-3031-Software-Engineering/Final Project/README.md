# Career Finder

## Tech stack

* MERN stack, MongoDB Express React NodeJs
* Atlas as 3rd party service for mongoDB
* Heroku for deployment


## Config

The following are the environment variables needed in production:

* DB_URI
* LOG_LEVEL
* NODE_ENV
* COOKIE_SECRET
* PAPERTRAIL_API_TOKEN

The papertrail api token is only needed if you are using papertrail as the logging service in Heroku.

## Deployment

We are using Heroku for deployment. If you are to deploy you need to be added to the Heroku project or start your own with the code.

To deploy to heroku setup heroku and then run the following command:

```
git push heroku master
```

## Available Scripts

Please note that any time the server is run in these scripts `nodemon` is used in place of `node` for easier development. If you are interested in how this works follow the nodemon In the project directory, you can run:

### `npm run-script dev`

Runs both the client app and the server app in development mode.<br>
Open [http://localhost:3000](http://localhost:3000) to view the client in the browser.

### `npm run-script client`

Runs just the client app in development mode.<br>
Open [http://localhost:3000](http://localhost:3000) to view the client in the browser.


### `npm run-script server`

Runs just the server in development mode.<br>


### `npm run build`

Builds the app for production to the `build` folder.<br>
It correctly bundles React in production mode and optimizes the build for the best performance.

If deploying to heroku this does not need to be run since it is handled by the heroku-postbuild script<br>

See the section about [deployment](https://facebook.github.io/create-react-app/docs/deployment) for more information.


## File structure
#### `client` - Holds the client application
- #### `public` - This holds all of our static files
- #### `src`
    - #### `assets` - This folder holds assets such as images, docs, and fonts
    - #### `components` - This folder holds all of the different components that will make up our views
    - #### `views` - These represent a unique page on the website i.e. Home or About. These are still normal react components
    - #### `App.js` - This is what renders all of our browser routes and different views
    - #### `index.js` - This is what renders the react app by rendering App.js, should not change
- #### `package.json` - Defines npm behaviors and packages for the client
#### `server` - Holds the server application
- #### `config` - This holds our configuration files, like mongoDB uri
- #### `controllers` - These hold all of the callback functions that each route will call
- #### `models` - This holds all of our data models
- #### `routes` - This holds all of our HTTP to URL path associations for each unique url
- #### `tests` - This holds all of our server tests that we have defined
- #### `server.js` - Defines npm behaviors and packages for the client
#### `package.json` - Defines npm behaviors like the scripts defined in the next section of the README
#### `.gitignore` - Tells git which files to ignore
#### `README` - This file!


## Filling Database with dummy data for Development

Make sure to make a `config.js` file inside `server/config` and have the right db uri (local or remote).

Then run the following

`node server/scripts/JSONToMongo.js`

This should create 3 careers in your MongoDB. These are for testing purposes only. You can add more careers to the `server/scripts/careers.json` if you want.
After filling the DB with dummy data, in your browser, go to `localhost:5000/api/careers` and you should see a response from the backend.


## Handoff Guidelines

Please get your user added to the Github repository by a current collaborator, and get invited to the Heroku project by the current project owner. This will allow you to make changes to the code and also deploy the application to Heroku.

### Running the application in Heroku

Make sure to have all the config environment variables in place before deploying to Heroku. The instructions to deploy [here](https://devcenter.heroku.com/articles/getting-started-with-nodejs#set-up) will help you get started.

### Beyond Heroku

The application will do well in Heroku for a while, depending on usage. If at some point there is scaling issues, Heroku allows the application to scale from 1 Dyno to many and also have an Auto Scaling feature that allows the application to scale depending on usage.

If at some point usage is high, and the price of Heroku is too much, we can move the project to a bigger cloud provider, e.g. AWS, Google Cloud, Microsoft Azure. The benefits of moving will be lower cost, increase security and increase configuration options. There are also drawbacks such as more configuration management that we will need to take care of.
