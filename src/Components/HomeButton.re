let component = ReasonReact.statelessComponent("HomeButtonRe");

let make = (~onClick, ~icon, ~style, children) => {
  ...component,
  render: _self =>
    <div
      className="button"
      onClick={
        event => {
          ReactEventRe.Mouse.stopPropagation(event);
          onClick(event);
        }
      }
      ?style>
      <span className="icon icon-home">
        <svg version="1.1" id="Layer_1" xmlns="http://www.w3.org/2000/svg" x="0px" y="0px" viewBox="0 0 25.6 25">
          <style> {ReasonReact.string(".st0{}")} </style>
          <g>
            <rect x="9.7" y="9.7" className="st0" width="1.9" height="2" />
            <rect x="9.7" y="6.8" className="st0" width="1.9" height="1.9" />
            <rect x="6.8" y="6.8" className="st0" width="1.9" height="1.9" />
            <rect x="6.8" y="9.7" className="st0" width="1.9" height="2" />
            <rect x="3.9" y="9.7" className="st0" width="2" height="1.9" />
            <path
              className="st0"
              d="M12,13.7H2V4.9h11.7v4.7c0.5-0.5,1.2-0.9,1.9-1.2V2.8c-0.1-0.5-0.5-0.9-1-0.9h-1.9V1c0-0.5-0.4-1-1-1c-0.5,0-1,0.4-1,1v1H4.9V0.9c0-0.5-0.5-0.9-1-0.9H3.8C3.3,0,2.9,0.5,2.9,1v1h-2C0.4,2,0,2.4,0,2.9v11.8c0,0.5,0.5,0.9,1,0.9h11.5C12.2,15,12.1,14.4,12,13.7z"
            />
            <path
              className="st0"
              d="M13.9,13.3c0,0.9,0.4,1.6,0.9,2.2c0.6,0.6,1.5,1,2.4,0.9c1.8,0,3.2-1.4,3.2-3.2c0-1.8-1.4-3.2-3.2-3.2c-0.7,0-1.2,0.2-1.7,0.5C14.5,11.1,13.9,12.1,13.9,13.3z"
            />
            <path className="st0" d="M17.2,18.1c-3.5,0-6.4,1.4-6.4,3.2v1.6h12.8v-1.6C23.6,19.6,20.7,18.1,17.2,18.1z" />
          </g>
        </svg>
      </span>
      {ReasonReact.createDomElement("span", ~props={"className": "button-text"}, children)}
    </div>,
};
