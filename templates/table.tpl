<table class="table table-striped">
  <thead> <tr>
    {{#each title in headings}}
      <th>{{title}}</th>
    {{/each}}
  </tr> </thead>
  <tbody>
    {{#each row in table}}
      <tr>
        {{#each cell in row}}
          <td>{{@raw cell}}</td>
        {{/each}}
      </tr>
    {{/each}}
  </tbody>
</table>
