## Handoff Guidelines

Please get added to the Github repo but a current collaborator, and get added to the Heroku project by the current project owner.

## Running the application in Heroku

Make sure to have all the config environment variables in place before deploying to Heroku. The instructions [here](https://devcenter.heroku.com/articles/getting-started-with-nodejs#set-up) will help you get started.

### Beyond Heroku

The application will do well in Heroku for a while, depending on usage. If at some point there is scaling issues, Heroku allows the application to scale from 1 Dyno to many and also have an Auto Scaling feature that allows the application to scale depending on usage.

If at some point usage is high, and the price of Heroku is too much, we can move the project to a bigger cloud provider, e.g. AWS, Google Cloud, Microsoft Azure. The benefits of moving will be lower cost, increase security and increase configuration options. There are also drawbacks such as more configuration management that we will need to take care of.
