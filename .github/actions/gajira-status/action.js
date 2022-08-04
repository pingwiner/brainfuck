const _ = require('lodash')
const Jira = require('./common/net/Jira')

module.exports = class {
  constructor ({ githubEvent, argv, config }) {
    this.Jira = new Jira({
      baseUrl: config.baseUrl,
      token: config.token,
      email: config.email,
    })

    this.config = config
    this.argv = argv
    this.githubEvent = githubEvent
  }

  async execute () {
    const { argv } = this

    const issueId = argv.issue
    const issue = await this.Jira.getIssue(issueId)
    const status = _.get(issue, 'fields.status.name')

    console.log(`${issueId} status is : ${status} .`)

    return { status: status }
  }

}
